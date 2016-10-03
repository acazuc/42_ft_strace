#include "ft_strace.h"

char *get_file_path(char *file, char **ev)
{
	char **path;
	char *tmp;
	int i;

	if (ft_strchr(file, '/'))
		return (file);
	tmp = NULL;
	i = 0;
	while (ev[i])
	{
		if (ft_strstr(ev[i], "PATH=") == ev[i])
		{
			tmp = ev[i] + 5;
			break;
		}
		i++;
	}
	if (!tmp)
		tmp = "/bin:/usr/bin";
		if (!(path = ft_strsplit(tmp, ':')))
	{
		ft_putendl_fd("Can't split path", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (path[i])
	{
		if (!(tmp = ft_strjoin_free1(path[i], "/")) || !(tmp = ft_strjoin_free1(tmp, file)))
		{
			ft_putendl_fd("Can't malloc prog path concat", 2);
			exit(EXIT_FAILURE);
		}
		if (!access(tmp, F_OK))
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}
