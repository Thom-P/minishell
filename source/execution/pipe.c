/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:26:21 by nadel-be          #+#    #+#             */
/*   Updated: 2023/03/02 18:11:18 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// pipefd[0] : le bout de lecture
// pipefd[1] : le bout d’écriture
// pipe: 0 == succes / -1 == error

void	pipe_init(t_exec *exec, int **fd)
{
	int	i;

	i = -1;
	while (++i < exec->nb_pipes)
	{
		fd[i] = ft_calloc(sizeof(*fd[i]), 2);
		pipe(fd[i]);
		if (pipe(fd[i]) == -1)
			return ;
	}
}

void	close_pipe(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < exec->nb_pipes)
	{
		close(exec->fd[i][0]);
		close(exec->fd[i][1]);
	}
}
