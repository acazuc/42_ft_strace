#include "ft_strace.h"

static pid_t child_pid;
int killed = 0;

int syscall_wait(pid_t pid, int *exit_status)
{
  int status;
  int sig;

  while (1)
  {
    ptrace(PTRACE_SYSCALL, pid, 0, 0);
    wait(&status);
    if (WIFEXITED(status) || WIFSIGNALED(status))
    {
      *exit_status = WEXITSTATUS(status);
      return (1);
    }
    if (WIFSTOPPED(status))
    {
      if ((sig = WSTOPSIG(status)) == SIGALRM)
        sig_handler(pid, sig);
      else if (WSTOPSIG(status) & 0x80)
        return (0);
      else if (sig != SIGTRAP)
        sig_handler(pid, sig);
    }
  }
}

static void signal_handler(int sig)
{
  (void)sig;
  kill(child_pid, SIGINT);
  ft_putstr("Process ");
  ft_putnbr(child_pid);
  ft_putendl(" detached");
  killed = 1;
}

void parent_launch(pid_t pid)
{
  struct user_regs_struct regs;
  int calling;
  int exit_status;
  int syscall_id;
  int args_nb;

  child_pid = pid;
  calling = 0;
  exit_status = 0;
  signal(SIGINT, signal_handler);
  ptrace_assert(PTRACE_SEIZE, pid, 0, (void*)PTRACE_O_TRACESYSGOOD, "PTRACE_SEIZE");
  ptrace_assert(PTRACE_INTERRUPT, pid, 0, 0, "PTRACE_INTERRUPT");
  while (1)
  {
    if (syscall_wait(pid, &exit_status))
      break;
    calling = 1;
    ptrace_assert(PTRACE_GETREGS, pid, 0, &regs, "PTRACE_GETREGSET");
    if (!killed)
    {
      syscall_id = regs.orig_rax;
      ft_putstr(syscalls_get_name(syscall_id));
      ft_putstr("(");
      args_nb = syscalls_get_args(syscall_id);
      if (args_nb == 0)
        ft_putstr("void");
      else
        print_args(args_nb, &regs);
    }
    if (syscall_wait(pid, &exit_status))
      break;
    ptrace_assert(PTRACE_GETREGS, pid, 0, &regs, "PTRACE_GETREGSET");
    if (!killed)
    {
      ft_putstr(") = ");
      ft_putnbr(regs.rax);
      ft_putchar('\n');
    }
  }
  if (killed)
    return;
  if (calling)
    ft_putendl(") = ?");
  ft_putstr("+++ exited with ");
  ft_putnbr(exit_status);
  ft_putendl(" +++");
}
