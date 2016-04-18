#include "ft_strace.h"

void print_args(int args_nb, struct user_regs_struct *regs)
{
  if (args_nb >= 1)
  {
    ft_putstr("\033[1;34m");
    ft_putul(regs->rdi);
    ft_putstr("\033[0;37m");
    if (args_nb >= 2)
    {
      ft_putstr(", ");
      ft_putstr("\033[1;34m");
      ft_putul(regs->rsi);
      ft_putstr("\033[0;37m");
      if (args_nb >= 3)
      {
        ft_putstr(", ");
        ft_putstr("\033[1;34m");
        ft_putul(regs->rdx);
        ft_putstr("\033[0;37m");
        if (args_nb >= 4)
        {
          ft_putstr(", ");
          ft_putstr("\033[1;34m");
          ft_putul(regs->rcx);
          ft_putstr("\033[0;37m");
          if (args_nb >= 5)
          {
            ft_putstr(", ");
            ft_putstr("\033[1;34m");
            ft_putul(regs->r8);
            ft_putstr("\033[0;37m");
            if (args_nb >= 6)
            {
              ft_putstr(", ");
              ft_putstr("\033[1;34m");
              ft_putul(regs->r9);
              ft_putstr("\033[0;37m");
            }
          }
        }
      }
    }
  }
}
