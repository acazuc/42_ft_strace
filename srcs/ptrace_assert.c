#include "ft_strace.h"

void ptrace_assert(enum __ptrace_request request, pid_t pid, void *addr, void *data, char *str)
{
	if (ptrace(request, pid, addr, data) == -1)
	{
		ft_putstr_fd("ft_strace: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" failed", 2);
		kill(pid, SIGKILL);
		exit(EXIT_FAILURE);
	}
}
