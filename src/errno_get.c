#include "ft_strace.h"

t_errno *g_errnos;

char *errno_get_name(int errno)
{
	int i;

	i = 0;
	while (g_errnos[i].value)
	{
		if (g_errnos[i].value == errno)
			return (g_errnos[i].name);
		i++;
	}
	return (g_errnos[i].name);
}

char *errno_get_desc(int errno)
{
	int i;

	i = 0;
	while (g_errnos[i].value)
	{
		if (g_errnos[i].value == errno)
			return (g_errnos[i].desc);
		i++;
	}
	return (g_errnos[i].desc);
}
