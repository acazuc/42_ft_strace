#include "ft_strace.h"

pid_t child_pid;
int killed = 0;

static void setemptyset()
{
	sigset_t empty;

	sigemptyset(&empty);
	sigprocmask(SIG_SETMASK, &empty, NULL);
}

static int syscall_wait(pid_t pid, int *exit_status, int *exit_return)
{
	sigset_t blocker;
	int status;
	int sig = 0;

	sigaddset(&blocker, SIGHUP);
	sigaddset(&blocker, SIGINT);
	sigaddset(&blocker, SIGQUIT);
	sigaddset(&blocker, SIGPIPE);
	sigaddset(&blocker, SIGTERM);
	while (1)
	{
		ptrace(PTRACE_SYSCALL, pid, 0, sig);
		setemptyset();
		waitpid(child_pid, &status, 0);
		sigprocmask(SIG_BLOCK, &blocker, NULL);
		sig = 0;
		if (WIFEXITED(status) || WIFSIGNALED(status))
		{
			*exit_return = status;
			*exit_status = WEXITSTATUS(status);
			return (1);
		}
		if (WIFSTOPPED(status))
		{
			sig = WSTOPSIG(status);
			if (sig & 0x80)
				return (0);
			else
				sig_handler(pid, sig);
		}
	}
}

static void signal_handler(int sig)
{
	(void)sig;
	printf("\033[0mProcess %d detached\n", child_pid);
	fflush(stdout);
	kill(child_pid, SIGINT);
	ptrace_assert(PTRACE_DETACH, child_pid, 0, 0, "PTRACE_DETACH");
	exit(EXIT_SUCCESS);
}

void parent_launch(pid_t pid)
{
	struct user_regs_struct regs;
	int calling;
	int exit_return;
	int exit_status;
	int syscall_id;
	int args_nb;
	int status;
	int floop = 0;

	child_pid = pid;
	calling = 0;
	exit_status = 0;
	signal(SIGINT, signal_handler);
	if (waitpid(pid, &status, WUNTRACED) == -1)
	{
		kill(pid, SIGKILL);
		exit(EXIT_FAILURE);
	}
	ptrace_assert(PTRACE_SEIZE, pid, 0, (void*)(PTRACE_O_TRACESYSGOOD), "PTRACE_SEIZE");
	while (1)
	{
		if (syscall_wait(pid, &exit_status, &exit_return))
			break;
		if (!killed)
		{
			ptrace_assert(PTRACE_GETREGS, pid, 0, &regs, "PTRACE_GETREGSET");
			syscall_id = regs.orig_rax;
			if (!killed)
			{
				calling = 1;
				if (floop)
				{
					printf("\033[1;35m%s\033[0m(", syscalls_get_name(syscall_id));
					args_nb = syscalls_get_args(syscall_id);
					if (args_nb == 0)
						printf("void");
					else
						print_args(args_nb, &regs, syscalls_get(syscall_id));
					fflush(stdout);
				}
				if (syscall_wait(pid, &exit_status, &exit_return))
					break;
				if (!killed)
				{
					calling = 0;
					ptrace_assert(PTRACE_GETREGS, pid, 0, &regs, "PTRACE_GETREGSET");
					if (floop)
					{printf("\033[1;37m) = ");
						if ((long long)regs.rax < 0)
							printf("\033[1;31m%d %s (%s)", -1, errno_get_name((int)-regs.rax), errno_get_desc((int)-regs.rax));
						else
							printf("\033[1;32m%llu", regs.rax);
						printf("\033[0m\n");
					}
					fflush(stdout);
				}
			}
		}
		floop = 1;
	}
	setemptyset();
	if (killed)
		return;
	if (calling)
		printf("\033[1;37m) = ?\n");
	if (WIFEXITED(exit_return))
	{
		printf("+++ exited with %d +++\n\033[0m", exit_status);
		exit(exit_status);
	}
	else if (WIFSIGNALED(exit_return))
	{
		if (WCOREDUMP(exit_return))
			printf("+++ Killed by %s +++ (core dumped)\n", signals_get(WTERMSIG(exit_return)));
		else
			printf("+++ Killed by %s +++\n", signals_get(WTERMSIG(exit_return)));
		printf("\033[0m");
		fflush(stdout);
		kill(getpid(), WTERMSIG(exit_return));
		return;
	}
	printf("\033[0m");
	fflush(stdout);
}
