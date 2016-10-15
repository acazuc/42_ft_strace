#include "ft_strace.h"

t_signal *g_signals;

void signals_init()
{
  t_signal signals[] = {{"SIG_0"},
{"SIGHUP"},
{"SIGINT"},
{"SIGQUIT"},
{"SIGILL"},
{"SIGTRAP"},
{"SIGABRT"},
{"SIGBUS"},
{"SIGFPE"},
{"SIGKILL"},
{"SIGUSR1"},
{"SIGSEGV"},
{"SIGUSR2"},
{"SIGPIPE"},
{"SIGALRM"},
{"SIGTERM"},
{"SIGSTKFLT"},
{"SIGCHLD"},
{"SIGCONT"},
{"SIGSTOP"},
{"SIGTSTP"},
{"SIGTTIN"},
{"SIGTTOU"},
{"SIGURG"},
{"SIGXCPU"},
{"SIGXFSZ"},
{"SIGVTALRM"},
{"SIGPROF"},
{"SIGWINCH"},
{"SIGIO"},
{"SIGPWR"},
{"SIGSYS"},
{"SIGRTMIN"}};
    if (!(g_signals = malloc(sizeof(signals))))
    {
      ft_putendl_fd("ft_strace: can't malloc signals names", 2);
      exit(EXIT_FAILURE);
    }
    ft_memcpy(g_signals, signals, sizeof(signals));
}
