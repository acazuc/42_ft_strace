#include "ft_strace.h"

void print_args(int args_nb, struct user_regs_struct *regs)
{
  if (args_nb >= 1)
  {
    printf("\033[1;34m%llu\033[0;37m", regs->rdi);
    if (args_nb >= 2)
    {
      printf(", \033[1;34m%llu\033[0;37m", regs->rsi);
      if (args_nb >= 3)
      {
        printf(", \033[1;34m%llu\033[0;37m", regs->rdx);
        if (args_nb >= 4)
        {
          printf(", \033[1;34m%llu\033[0;37m", regs->rcx);
          if (args_nb >= 5)
          {
            printf(", \033[1;34m%llu\033[0;37m", regs->r8);
            if (args_nb >= 6)
            {
              printf(", \033[1;34m%llu\033[0;37m", regs->r9);
            }
          }
        }
      }
    }
  }
}
