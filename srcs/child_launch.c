#include "ft_strace.h"

void child_launch(char **av, char *file)
{
  kill(getpid(), SIGSTOP);
  if (execv(file, av + 1) == -1)
  {
    ft_putendl_fd("ft_strace: can't exec bin", 2);
    exit(EXIT_FAILURE);
  }
}
