/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/01/26 15:02:58 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define ARGSERROR "pipex: usage:\tfilein cmd1 cmd2 ... cmdn fileout\n\
\t\tor here_dock delimiter cmd1 cmd2 ... cmdn fileout"

void	error(char *message)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putendl_fd(message, 2);
	ft_garbage_colector(0, 1, 1);
}

char	*ft_read_nl(int fd)
{
	int		size;
	char	*buffer;
	char	tuffer[3333 + 1];

	buffer = ft_calloc(1, 1);
	size = read(fd, tuffer, 3333);
	while (size)
	{
		tuffer[size] = 0;
		buffer = ft_strjoin(buffer, tuffer);
		if (ft_strcontain(buffer, '\n'))
			break ;
		size = read(fd, tuffer, 3333);
	}
	return (buffer);
}

void	herdock(char *sub)
{
	char	*herd;

	while (1)
	{
		ft_putstr("heredoc> ");
		herd = ft_read_nl(0);
		if (ft_strlen(herd) > 0)
			herd[ft_strlen(herd) - 1] = 0;
		if (ft_strcmp(sub, herd) == 0)
		{
			free(herd);
			return ;
		}
		else
			ft_putendl_fd(herd, pipi()->fd[1]);
		free(herd);
		herd = 0;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	int		w;
	char	**split;
	int		mode;

	if (argc < 4)
		error(ARGSERROR);
	if (ft_strcmp("here_doc", argv[1]) && argc < 5)
		error(ARGSERROR);
	i = 0;
	mode = 0;
	if (ft_strcmp("here_doc", argv[1]) == 0 && ++i)
		mode = 1;
	filein(argv[++i], mode);
	while (++i < argc - 1)
	{
		wait(&w);
		split = ft_split(argv[i], ' ');
		execute(split);
		ft_free_pp((void **)split);
	}
	fileout(argv[argc - 1], mode);
}
