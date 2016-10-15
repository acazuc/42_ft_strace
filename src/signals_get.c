#include "ft_strace.h"

t_signal *g_signals;

char *signals_get(int sig)
{
	if (sig > 32 || sig < 0)
		return ("EUNKNOWN");
	return (g_signals[sig].name);
}
