#include "ft_strace.h"

pid_t child_pid;
int killed = 0;

int syscall_wait(pid_t pid, int *exit_status, int *exit_return)
{
	int status;
	int sig;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, pid, 0, 0);
		wait(&status);
		if (WIFEXITED(status) || WIFSIGNALED(status))
		{
			*exit_return = status;
			*exit_status = WEXITSTATUS(status);
			return (1);
		}
		if (WIFSTOPPED(status))
		{
			if ((sig = WSTOPSIG(status)) == SIGALRM)
				sig_handler(pid, sig);
			else if (WSTOPSIG(status) & 0x80)
				return (0);
			else
				sig_handler(pid, sig);
		}
	}
}

static void signal_handler(int sig)
{
	(void)sig;
	printf("Process %d detached", child_pid);
	fflush(stdout);
	kill(child_pid, SIGINT);
	killed = 1;
	ptrace_assert(PTRACE_DETACH, child_pid, 0, 0, "PTRACE_DETACH");
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
		calling = 1;
		if (!killed)
		{
			ptrace_assert(PTRACE_GETREGS, pid, 0, &regs, "PTRACE_GETREGSET");
			syscall_id = regs.orig_rax;
			if (!killed)
			{
				printf("\033[1;35m%s\033[1;37m(", syscalls_get_name(syscall_id));
				args_nb = syscalls_get_args(syscall_id);
				if (args_nb == 0)
					printf("void");
				else
					print_args(args_nb, &regs, syscalls_get(syscall_id));
				if (syscall_wait(pid, &exit_status, &exit_return))
					break;
				if (!killed)
				{
					ptrace_assert(PTRACE_GETREGS, pid, 0, &regs, "PTRACE_GETREGSET");
					printf("\033[1;37m) = ");
					if ((long long)regs.rax < 0)
						printf("\033[1;31m%d %s (%s)", -1, errno_get_name(-regs.rax), errno_get_desc(-regs.rax));
					else
						printf("\033[1;32m%llu", regs.rax);
					printf("\033[0;37m\n");
					fflush(stdout);
				}
			}
		}
	}
	if (killed)
		return;
	if (calling)
		printf("\033[1;37m) = ?\n");
	if (WIFEXITED(exit_return))
		printf("+++ exited with %d +++\n", exit_status);
	else if (WIFSIGNALED(exit_return))
	{
		if (WCOREDUMP(exit_return))
			printf("+++ Killed by %s +++ (core dumped)\n", signals_get(WTERMSIG(exit_return)));
		else
			printf("+++ Killed by %s +++\n", signals_get(WTERMSIG(exit_return)));
	}
	fflush(stdout);
}
