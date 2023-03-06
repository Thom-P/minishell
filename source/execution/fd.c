/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:03:15 by nadel-be          #+#    #+#             */
/*   Updated: 2023/03/06 16:59:12 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	search_fd(char *file, enum e_redir redir, int is_child)
{
	int	fd;

	fd = -1;
	if (redir == in)
		fd = open(file, O_RDONLY, 0644);
	if (redir == out)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (redir == append)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, "jmsh: %s: ", file);
		perror("");
		if (is_child)
			my_exit("", EXIT_FAILURE);
	}
	return (fd);
}

void	fd_redir(t_exec *exec, t_block *blocks)
{
	int	i;
	int	is_child;

	is_child = 1;
	i = -1;
	while (blocks->files[++i])
	{
		if (blocks->redir[i] == in)
		{
			exec->fd_in = search_fd(blocks->files[i], blocks->redir[i], is_child);
			dup2(exec->fd_in, STDIN_FILENO);
			close(exec->fd_in);
		}
		if (blocks->redir[i] == out || blocks->redir[i] == append)
		{
			exec->fd_out = search_fd(blocks->files[i], blocks->redir[i], is_child);
			dup2(exec->fd_out, STDOUT_FILENO);
			close(exec->fd_out);
		}
	}
}

int	fd_redir_one_block(t_block *blocks)
{
	int	i;
	int	fd_in;
	int	fd_out;
	int	is_child;

	is_child = 0;
	i = -1;
	while (blocks->files[++i])
	{
		if (blocks->redir[i] == in)
		{
			fd_in = search_fd(blocks->files[i], blocks->redir[i], is_child);
			if (fd_in == -1)
				return (-1);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (blocks->redir[i] == out || blocks->redir[i] == append)
		{
			fd_out = search_fd(blocks->files[i], blocks->redir[i], is_child);
			if (fd_out == -1)
				return (-1);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
	}
	return (0);
}
