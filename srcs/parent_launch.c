#include "ft_strace.h"

static pid_t child_pid;

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
      else
        sig_handler(pid, sig);
    }
  }
}

static void signal_handler(int sig)
{
  if (sig == SIGINT)
  {
    kill(child_pid, SIGINT);
    exit(EXIT_SUCCESS);
  }
}

void parent_launch(pid_t pid)
{
  struct user_regs_struct regs;
  int calling;
  int exit_status;
  int syscall_id;

  child_pid = pid;
  calling = 0;
  exit_status = 0;
  signal(SIGINT, signal_handler);
  if (ptrace(PTRACE_SEIZE, pid, 0, PTRACE_O_TRACESYSGOOD) == -1)
  {
    ft_putendl_fd("PTRACE_SEIZE failed", 2);
    kill(child_pid, SIGKILL);
    exit(EXIT_FAILURE);
  }
  if (ptrace(PTRACE_INTERRUPT, pid, 0, 0) == -1)
  {
    ft_putendl_fd("PTRACE_INTERRUPT failed", 2);
    kill(child_pid, SIGKILL);
    exit(EXIT_FAILURE);
  }
  while (1)
  {
    if (syscall_wait(pid, &exit_status))
      break;
    calling = 1;
    if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1)
    {
      ft_putendl_fd("PTRACE_GETREGSET failed", 2);
      kill(child_pid, SIGKILL);
      exit(EXIT_FAILURE);
    }
    syscall_id = regs.orig_rax;
    ft_putstr(syscalls_get_name(syscall_id));
    ft_putstr("(");
    int args_nb = syscalls_get_args(syscall_id);
    if (args_nb == 0)
    {
      ft_putstr("void");
    }
    else
    {
      if (args_nb >= 1)
      {
        ft_putul(regs.rdi);
        if (args_nb >= 2)
        {
          ft_putstr(", ");
          ft_putul(regs.rsi);
          if (args_nb >= 3)
          {
            ft_putstr(", ");
            ft_putul(regs.rdx);
            if (args_nb >= 4)
            {
              ft_putstr(", ");
              ft_putul(regs.rcx);
              if (args_nb >= 5)
              {
                ft_putstr(", ");
                ft_putul(regs.r8);
                if (args_nb >= 6)
                {
                  ft_putstr(", ");
                  ft_putul(regs.r9);
                }
              }
            }
          }
        }
      }
    }
    if (syscall_wait(pid, &exit_status))
      break;
    if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1)
    {
      ft_putendl_fd("PTRACE_GETREGSET failed", 2);
      kill(child_pid, SIGKILL);
      exit(EXIT_FAILURE);
    }
    ft_putstr(") = ");
    ft_putnbr(regs.rax);
    ft_putchar('\n');
    ptrace(PTRACE_CONT, pid, 0);
  }
  if (calling)
    ft_putendl(") = ?");
  ft_putstr("+++ exited with ");
  ft_putnbr(exit_status);
  ft_putendl(" +++");
}
