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
  ft_putstr("Process ");
  ft_putnbr(child_pid);
  ft_putendl(" detached");
  kill(child_pid, SIGINT);
  killed = 1;
  ptrace_assert(PTRACE_DETACH, child_pid, 0, 0, "PTRACE_DETACH");
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
    if (!killed)
    {
      ptrace_assert(PTRACE_GETREGS, pid, 0, &regs, "PTRACE_GETREGSET");
      syscall_id = regs.orig_rax;
      ft_putstr("\033[1;35m");
      ft_putstr(syscalls_get_name(syscall_id));
      ft_putstr("\033[1;37m");
      ft_putstr("(");
      args_nb = syscalls_get_args(syscall_id);
      if (args_nb == 0)
        ft_putstr("void");
      else
        print_args(args_nb, &regs);
      if (syscall_wait(pid, &exit_status))
        break;
      if (!killed)
      {
        ptrace_assert(PTRACE_GETREGS, pid, 0, &regs, "PTRACE_GETREGSET");
        ft_putstr("\033[1;37m) = ");
        if ((long long)regs.rax < 0)
        {
          ft_putstr("\033[1;31m");
          ft_putnbr(regs.rax);
          ft_putchar(' ');
          ft_putstr(errno_get_name(-regs.rax));
          ft_putstr(" (");
          ft_putstr(errno_get_desc(-regs.rax));
          ft_putstr(")");
        }
        else
        {
          ft_putstr("\033[1;32m");
          ft_putnbr(regs.rax);
        }
        ft_putstr("\033[0;37m");
        ft_putchar('\n');
      }
    }
  }
  if (killed)
    return;
  if (calling)
    ft_putendl("\033[1;37m) = ?");
  ft_putstr("+++ exited with ");
  ft_putnbr(exit_status);
  ft_putendl(" +++");
}
