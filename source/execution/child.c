/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:46:46 by nadel-be          #+#    #+#             */
/*   Updated: 2023/03/06 14:03:20 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	double_dup(int first, int second)
{
	dup2(first, STDIN_FILENO);
	dup2(second, STDOUT_FILENO);
}

void	while_dup(t_exec *exec, int n)
{
	if (n == 0)
		dup2(exec->fd[n][1], STDOUT_FILENO);
	else if (n == exec->nb_cmd - 1)
		dup2(exec->fd[n - 1][0], STDIN_FILENO);
	else
		double_dup(exec->fd[n - 1][0], exec->fd[n][1]);
}

// returns index of bultin in list below or -1 if not a builtin
int	get_index_builtin(char *cmd, char *names[N_BUILTIN])
{
	int		ind;

	if (cmd == NULL)
		return (-1);
	ind = 0;
	while (ind < N_BUILTIN)
	{
		if (ft_strncmp(cmd, names[ind], ft_strlen(names[ind]) + 1) == 0)
			return (ind);
		ind++;
	}
	return (-1);
}

void	child(t_exec *exec, t_block *blocks, t_builtin *builtin, char **my_env)
{
	char	*cmd;
	int		ind_built;

	if (exec->nb_blocks > 1)
		while_dup(exec, exec->n);
	fd_redir(exec, blocks);
	close_pipe(exec);
	ind_built = get_index_builtin(blocks->cmd_args[0], builtin -> names);
	if (ind_built != -1)
	{	
		g_status = builtin -> f_ptr[ind_built](blocks->n_arg,
				blocks->cmd_args, &my_env);
		exit(g_status); //TODO: exit a finir (free?)
	}
	else
	{
		if (ft_strchr(blocks->cmd_args[0], '/'))
		{
			cmd = ft_strdup(blocks->cmd_args[0]);
			if (cmd == NULL)
				my_exit("mallor error in child\n", EXIT_FAILURE);
		}
		else
		{
			cmd = find_cmd(exec, blocks->cmd_args[0]);
			if (cmd == NULL)
			{
				g_status = 127;
				my_exit("jmsh: command not found\n", g_status);
			}
		}
		g_status = execve(cmd, blocks->cmd_args, my_env);
		if (g_status == -1)
		{
			perror("jmsh");
			g_status = 126;
			my_exit("", g_status);
			// error_exit(MSG_INV_CMD, data);
		}
	}
}

	// execve(cmd, blocks->cmd_args, my_env);