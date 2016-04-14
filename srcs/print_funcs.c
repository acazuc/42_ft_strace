#include "ft_strace.h"

void print_args(int args_nb, struct user_regs_struct *regs)
{
  if (args_nb >= 1)
  {
    ft_putul(regs->rdi);
    if (args_nb >= 2)
    {
      ft_putstr(", ");
      ft_putul(regs->rsi);
      if (args_nb >= 3)
      {
        ft_putstr(", ");
        ft_putul(regs->rdx);
        if (args_nb >= 4)
        {
          ft_putstr(", ");
          ft_putul(regs->rcx);
          if (args_nb >= 5)
          {
            ft_putstr(", ");
            ft_putul(regs->r8);
            if (args_nb >= 6)
            {
              ft_putstr(", ");
              ft_putul(regs->r9);
            }
          }
        }
      }
    }
  }
}
