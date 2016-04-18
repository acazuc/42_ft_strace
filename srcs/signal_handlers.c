#include "ft_strace.h"

int killed;


static void continue_ptrace(pid_t pid, int sig)
{
  if (ptrace(PTRACE_CONT, pid, NULL, sig) == -1)
  {
      ft_putendl_fd("PTRACE_CONT failed", 2);
      kill(pid, SIGKILL);
      exit(EXIT_FAILURE);
  }
  if (ptrace(PTRACE_INTERRUPT, pid, NULL, 0) == -1)
  {
      ft_putendl_fd("PTRACE_INTERRUPT failed", 2);
      kill(pid, SIGKILL);
      exit(EXIT_FAILURE);
  }
}

void sig_handler(pid_t pid, int sig)
{
  siginfo_t siginfo;

  if (killed)
    return;
  ft_putstr("\033[1;37m--- ");
  ptrace_assert(PTRACE_GETSIGINFO, pid, NULL, &siginfo, "PTRACE_GETSIGINFO");
  ft_putstr(signals_get(sig));
  printf(" { si_signo=%s, si_code=%d, si_pid=%d, si_uid=%d} ---\n", signals_get(sig), siginfo.si_code, siginfo.si_pid, siginfo.si_uid);
  continue_ptrace(pid, sig);
}
