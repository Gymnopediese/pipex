/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2023/01/31 16:39:28 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

#define PATH "/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/usr/bin:/bin:\
/usr/sbin:/sbin:/opt/X11/bin:/Library/Frameworks/Mono.framework/Versions/Current\
/Commands:/Users/albaud/opt/anaconda3/bin:/Users/albaud/opt/anaconda3/condabin:/\
opt/homebrew/bin:/opt/homebrew/sbin"

char	*from_path(char *exec)
{
	char	**paths;
	int		i;
	char	buff[777];

	i = -1;
	paths = ft_split(PATH, ':');
	if (paths == 0)
		ft_garbage_colector(0, 1, 1);
	while (paths[++i])
	{
		ft_strcpy(buff, paths[i]);
		ft_strcat(buff, "/");
		ft_strcat(buff, exec);
		if (access(buff, F_OK) == 0)
		{
			ft_free_pp((void **)paths);
			return (ft_strdup(buff));
		}
	}
	ft_free_pp((void **)paths);
	return (0);
}

char	*make_path(char *exec)
{
	if (exec && exec[0] == '.' && exec[1] == '/')
	{
		if (access(&exec[2], F_OK) == 0)
			return (exec);
		else
			error("invalid command");
	}
	else
		return (from_path(exec));
	return (0);
}

int	exute_process(char **argv, const char *file, int *fd)
{
	close(fd[0]);
	dup2(pipi()->fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	execve(file, argv, 0);
	ft_putstr_fd(file, 2);
	free((void *)file);
	ft_putendl_fd(" failed to execute\n", 2);
	return (1);
}

int	wait_execution(int *fd)
{
	int	wstatus;
	int	status_code;

	errno = 0;
	status_code = 0;
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		status_code = WEXITSTATUS(wstatus);
	close(fd[1]);
	close(pipi()->fd[0]);
	if (pipe(pipi()->fd) == -1)
		error("cannot open pipe");
	fd_fd_injection(pipi()->fd[1], fd[0]);
	close(pipi()->fd[1]);
	close(fd[0]);
	return (status_code);
}

// Execute "file" and return it's return value
int	execute(char **args)
{
	int			pid;
	int			fd[2];
	char		*path;

	path = make_path(args[0]);
	if (pipe(fd) == -1)
		error("cannot open pipe");
	pid = fork();
	if (pid == 0)
		return (exute_process(args, path, fd));
	else
		return (wait_execution(fd));
}
