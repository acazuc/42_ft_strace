#ifndef FT_STRACE_H
# define FT_STRACE_H

# include "../libft/includes/libft.h"
# include <sys/ptrace.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/user.h>
# include <sys/reg.h>
# include <stdio.h>

typedef struct s_syscall t_syscall;
typedef struct s_signal t_signal;

struct s_syscall
{
  int args;
  char *name;
};

struct s_signal
{
  char *name;
};

void print_help(void);
void syscalls_init(void);
char *syscalls_get_name(int syscall);
int syscalls_get_args(int syscall);
void child_launch(char **av, char *file);
void parent_launch(pid_t pid);
char *get_file_path(char *file, char **ev);
void signals_init(void);
char *signals_get(int sig);
void sig_handler(pid_t pid, int sig);
void sigalrm_handler(pid_t pid);
void print_args(int args_nb, struct user_regs_struct *regs);
void ptrace_assert(enum __ptrace_request request, pid_t pid, void *addr, void *data, char *str);

#endif
