/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:46:46 by nadel-be          #+#    #+#             */
/*   Updated: 2023/03/02 18:11:26 by nadel-be         ###   ########.fr       */
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
		//TODO: faire une vraie erreur avec status
		printf("ceci est une erreur de FD\n");
	}
	return (fd);
}

void	double_dup(int first, int second)
{
	dup2(first, STDIN_FILENO);
	dup2(second, STDOUT_FILENO);
}

void	child(t_exec *exec, t_block *blocks, char **my_env, int n)
{
	int		i;
	char	*cmd;

	i = -1;
	if (n == 0)
		dup2(exec->fd[n][1], STDOUT_FILENO);
	else if (n == exec->nb_cmd - 1)
		dup2(exec->fd[n - 1][0], STDIN_FILENO);
	else
		double_dup(exec->fd[n - 1][0], exec->fd[n][1]);
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
	close_pipe(exec);
	//TODO: builtin a verif avec if
	//TODO: verif si deja slash on lance direct
	cmd = find_cmd(exec, blocks->cmd_args[0]);
	// g_status = execve(cmd, blocks->cmd_args, my_env);
	execve(cmd, blocks->cmd_args, my_env);
}

	// if (g_status == -1)
	// {
	// 	data->status = 127;
	// 	error_exit(MSG_INV_CMD, data);
	// }