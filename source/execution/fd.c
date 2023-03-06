/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:03:15 by nadel-be          #+#    #+#             */
/*   Updated: 2023/03/06 14:54:09 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	search_fd(char *file, enum e_redir redir)
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
		//TODO: faire une vraie erreur avec status dont fichier introuvable et celui qu'on a pas le droit (avec le cmod)
		printf("ceci est une erreur de FD\n");
	}
	return (fd);
}

void	fd_redir(t_exec *exec, t_block *blocks)
{
	int	i;

	i = -1;
	while (blocks->files[++i])
	{
		if (blocks->redir[i] == in)
		{
			exec->fd_in = search_fd(blocks->files[i], blocks->redir[i]);
			dup2(exec->fd_in, STDIN_FILENO);
			close(exec->fd_in);
		}
		if (blocks->redir[i] == out || blocks->redir[i] == append)
		{
			exec->fd_out = search_fd(blocks->files[i], blocks->redir[i]);
			dup2(exec->fd_out, STDOUT_FILENO);
			close(exec->fd_out);
		}
	}
}

void	fd_redir_one_block(t_block *blocks)
{
	int	i;
	int	fd_in;
	int	fd_out;

	i = -1;
	while (blocks->files[++i])
	{
		if (blocks->redir[i] == in)
		{
			fd_in = search_fd(blocks->files[i], blocks->redir[i]);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (blocks->redir[i] == out || blocks->redir[i] == append)
		{
			fd_out = search_fd(blocks->files[i], blocks->redir[i]);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
	}

}
