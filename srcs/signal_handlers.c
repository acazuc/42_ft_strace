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
  continue_ptrace(pid, sig);
  if (killed)
    return;
  ft_putstr("--- ");
  ft_putstr(signals_get(sig));
  ft_putstr(" ---\n");
}
