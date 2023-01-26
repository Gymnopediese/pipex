/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2022/12/09 11:49:05 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	exute_process(char **argv, const char	*file, int *fd)
{
	close(fd[0]);
	dup2(pipi()->fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	execve(file, argv, 0);
	ft_putstr_fd(file, 2);
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

void	make_path(char *path, char *arg)
{
	path[0] = 0;
	ft_strcat(path, "/bin/");
	ft_strcat(path, arg);
	if (access(path, F_OK) == 0)
		return ;
	path[0] = 0;
	ft_strcat(path, "/usr/bin/");
	ft_strcat(path, arg);
	if (access(path, F_OK) == 0)
		return ;
}

// Execute "file" and return it's return value
int	execute(char **args)
{
	int			pid;
	int			fd[2];
	char		path[100];

	path[0] = 0;
	make_path(path, args[0]);
	if (pipe(fd) == -1)
		error("cannot open pipe");
	pid = fork();
	if (pid == 0)
		return (exute_process(args, path, fd));
	else
		return (wait_execution(fd));
}
