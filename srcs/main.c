#include "ft_strace.h"

int main(int ac, char **av, char **ev)
{
	struct stat tmp;
	char *file;
	pid_t pid;

	if (ac < 2)
		print_help();
	if (!(file = get_file_path(av[1], ev)))
	{
		ft_putendl_fd("Can't find exec in path", 2);
		exit(EXIT_SUCCESS);
	}
	if (stat(file, &tmp) == -1)
	{
		ft_putstr_fd("ft_strace: \"", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("\": No such file or directory", 2);
		exit(EXIT_FAILURE);
	}
	syscalls_init();
	signals_init();
	errno_init();
	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("ft_strace: failed to fork", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_launch(av, file);
	else
		parent_launch(pid);
}
