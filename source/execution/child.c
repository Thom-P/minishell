/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:46:46 by nadel-be          #+#    #+#             */
/*   Updated: 2023/02/24 12:15:10 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	double_dup(int first, int second)
{
	dup2(first, STDIN_FILENO);
	dup2(second, STDOUT_FILENO);
}

void	child(t_pipex *data, int **fd, char **envp, int n)
{
	int	status;

	status = 0;
	if (n == 0)
		double_dup(data->fd_in, fd[n][1]);
	else if (n == data->nb_cmd - 1)
		double_dup(fd[n - 1][0], data->fd_out);
	else
		double_dup(fd[n - 1][0], fd[n][1]);
	close_pipe(data);
	status = execve(find_cmd(data, data->tab_cmd[n][0]),
			data->tab_cmd[n], envp);
	if (status == -1)
	{
		data->status = 127;
		error_exit(MSG_INV_CMD, data);
	}
}
