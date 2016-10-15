#include "ft_strace.h"

t_syscall *g_syscalls;

char *syscalls_get_name(int syscall)
{
	if (syscall > 313 || syscall < 0)
		return (NULL);
	return (g_syscalls[syscall].name);
}

int syscalls_get_args(int syscall)
{
	if (syscall > 313 || syscall < 0)
		return (0);
	return (g_syscalls[syscall].args);
}

t_syscall syscalls_get(int syscall)
{
	t_syscall empty = {0, "unknown", {}};
	if (syscall > 313 || syscall < 0)
		return (empty);
	return (g_syscalls[syscall]);
}
