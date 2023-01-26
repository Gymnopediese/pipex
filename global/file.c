/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2023/01/26 14:50:43 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	filein(char *filename, int mode)
{
	int	fd;

	fd = 0;
	if (pipe(pipi()->fd) == -1)
		error("cannot open pipe");
	if (mode == 0)
	{
		fd = open(filename, O_RDONLY);

		if (fd == -1)
			error(strerror(errno));
		fd_fd_injection(pipi()->fd[1], fd);
		close(fd);
	}
	else
		herdock(filename);
	close(pipi()->fd[1]);
}

void	fileout(char *filename, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		error("cannot open or create file");
	fd_fd_injection(fd, pipi()->fd[0]);
	close(pipi()->fd[0]);
	close(fd);
}
