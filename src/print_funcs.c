#include "ft_strace.h"

pid_t	child_pid;

static int contains_zero(long l)
{
	return (!((l >> 56) & 0xff)
			|| !((l >> 48) & 0xff)
			|| !((l >> 40) & 0xff)
			|| !((l >> 32) & 0xff)
			|| !((l >> 24) & 0xff)
			|| !((l >> 16 & 0xff))
			|| !((l >> 8) & 0xff)
			|| !(l & 0xff));
}

static char *peek_str(void *addr)
{
	size_t	count;
	char	*str;
	long	tmp;

	if (!(str = malloc(sizeof(*str) * 38)))
	{
		kill(child_pid, SIGKILL);
		exit(EXIT_FAILURE);
	}
	ft_bzero(str, 38);
	ft_strcat(str, "\"");
	count = 0;
	while (count < 32)
	{
		errno = 0;
		if ((tmp = ptrace(PTRACE_PEEKDATA, child_pid, addr + count, NULL)) == -1 && errno)
		{
			kill(child_pid, SIGKILL);
			exit(EXIT_FAILURE);
		}
		ft_memcpy(str + 1 + count, &tmp, sizeof(tmp));
		count += sizeof(long);
		if (contains_zero(tmp))
			break;
	}
	ft_strcat(str, "\"");
	if (count == 32)
		ft_strcat(str, "...");
	return (str);
}

static void print_arg(long val, enum e_syscall_param_type type)
{
	if (type == PARAM_NUMBER)
	{
		printf("\033[1;34m%llu\033[0;37m", (long long)val);
	}
	else if (type == PARAM_ADDR)
	{
		if (val == 0)
			printf("\033[1;34mNULL\033[0;37m");
		else
			printf("\033[1;34m0x%llx\033[0;37m", (unsigned long long)val);
	}
	else if (type == PARAM_STRING)
	{
		char *str = peek_str((void*)val);
		printf("\033[1;34m%s\033[0;37m", str);
		free(str);
	}
}

void print_args(int args_nb, struct user_regs_struct *regs, t_syscall syscall)
{
	if (args_nb >= 1)
	{
		print_arg(regs->rdi, syscall.type[0]);
		if (args_nb >= 2)
		{
			printf(", ");
			print_arg(regs->rsi, syscall.type[1]);
			if (args_nb >= 3)
			{
				printf(", ");
				print_arg(regs->rdx, syscall.type[2]);
				if (args_nb >= 4)
				{
					printf(", ");
					print_arg(regs->rcx, syscall.type[3]);
					if (args_nb >= 5)
					{
						printf(", ");
						print_arg(regs->r8, syscall.type[4]);
						if (args_nb >= 6)
						{
							printf(", ");
							print_arg(regs->r9, syscall.type[5]);
						}
					}
				}
			}
		}
	}
}
