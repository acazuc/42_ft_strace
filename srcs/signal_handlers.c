#include "ft_strace.h"

int killed;

static void continue_ptrace(pid_t pid, int sig)
{
	int		status;

	if (sig != SIGCONT)
		ptrace_assert(PTRACE_CONT, pid, NULL, (void*)(unsigned long)sig, "PTRACE_CONT");
	if (sig == SIGSTOP)
	{
		if (waitpid(pid, &status, WUNTRACED) == -1)
		{
			ft_putendl("waitpid failed");
			kill(pid, SIGKILL);
			exit(EXIT_FAILURE);
		}
		ptrace_assert(PTRACE_LISTEN, pid, NULL, NULL, "PTRACE_LISTEN");
		if (waitpid(pid, &status, WCONTINUED) == -1)
		{
			ft_putendl("waitpid failed");
			kill(pid, SIGKILL);
			exit(EXIT_FAILURE);
		}
		return;
	}
}

void sig_handler(pid_t pid, int sig)
{
	siginfo_t siginfo;

	if (killed)
		return;
	ptrace_assert(PTRACE_GETSIGINFO, pid, NULL, &siginfo, "PTRACE_GETSIGINFO");
	printf("\033[1;37m--- ");
	printf("%s", signals_get(sig));
	printf(" { si_signo=%s, si_code=%d, si_pid=%d, si_uid=%d} ---\n", signals_get(sig), siginfo.si_code, siginfo.si_pid, siginfo.si_uid);
	continue_ptrace(pid, sig);
}
