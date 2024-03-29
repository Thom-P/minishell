/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:47:32 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/07 15:41:25 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_exec_struct(t_exec *exec, t_list *exec_blocks, char **my_env)
{
	int	i;

	i = -1;
	exec->nb_blocks = ft_lstsize(exec_blocks);
	exec->nb_pipes = exec->nb_blocks - 1;
	exec->nb_cmd = exec->nb_blocks;
	exec->fd = ft_calloc(sizeof(*exec->fd), exec->nb_pipes);
	if (exec->fd == NULL)
		my_exit("Malloc error in init_exec_struct\n", EXIT_FAILURE);
	exec->pid = ft_calloc(sizeof(exec->pid), exec->nb_cmd);
	if (exec->pid == NULL)
		my_exit("Malloc error in init_exec_struct\n", EXIT_FAILURE);
	exec -> path = NULL;
	while (my_env[++i])
	{
		if (ft_strncmp(my_env[i], "PATH=", 5) == 0)
		{	
			exec->path = ft_split(&my_env[i][5], ':');
			if (exec -> path == NULL)
				my_exit("ft_split error in init_exec_struct", EXIT_FAILURE);
			break ;
		}
	}
	return ;
}

void	free_path_and_fd(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < exec -> nb_pipes)
		free(exec -> fd[i]);
	free(exec -> fd);
	i = -1;
	if (exec -> path == NULL)
		return ;
	while (exec->path[++i])
		free(exec->path[i]);
	free(exec->path);
	return ;
}

int	launch_exec(t_list *exec_blocks, t_builtin *builtin, char ***my_env)
{
	t_exec	exec;
	int		stat_last_pid;

	init_exec_struct(&exec, exec_blocks, *my_env);
	if (exec.nb_pipes > 0)
		pipe_init(&exec, exec.fd);
	exec.n = -1;
	while (++(exec.n) < exec.nb_cmd)
	{
		fork_init(&exec, (t_block *)(exec_blocks -> content), builtin, *my_env);
		exec_blocks = exec_blocks->next;
	}
	if (exec.nb_pipes > 0)
		close_pipe(&exec);
	exec.n = -1;
	while (++(exec.n) < exec.nb_cmd - 1)
		waitpid(exec.pid[exec.n], NULL, 0);
	waitpid(exec.pid[++(exec.n)], &stat_last_pid, 0);
	if (WIFEXITED(stat_last_pid))
		g_status = WEXITSTATUS(stat_last_pid);
	else if (WIFSIGNALED(stat_last_pid))
		g_status = WTERMSIG(stat_last_pid) + 128;
	free_path_and_fd(&exec);
	free(exec.pid);
	return (g_status);
}

void	e_built(t_list *exec_blocks, t_builtin *builtin,
	int ind_built, char ***ptr_my_envp)
{	
	int		ac;
	char	**av;
	int		std_save[2];

	ac = ((t_block *)exec_blocks -> content)-> n_arg;
	av = ((t_block *)exec_blocks -> content)-> cmd_args;
	std_save[1] = dup(STDOUT_FILENO);
	std_save[0] = dup(STDIN_FILENO);
	if (fd_redir_one_block(exec_blocks -> content) == 0)
	{
		if (av[0] != NULL)
			g_status = builtin -> f_ptr[ind_built](ac, av, ptr_my_envp);
	}	
	else
		g_status = 1;
	dup2(std_save[1], STDOUT_FILENO);
	dup2(std_save[0], STDIN_FILENO);
	return ;
}

void	exec_line(t_list *exec_blocks, char ***ptr_my_envp, t_builtin *builtin)
{
	int		ind_built;
	char	**av;

	av = ((t_block *)exec_blocks -> content)-> cmd_args;
	if (exec_blocks -> next == NULL)
	{
		ind_built = get_index_builtin(av[0], builtin -> names);
		if (ind_built != -1 || av[0] == NULL)
		{	
			e_built(exec_blocks, builtin, ind_built, ptr_my_envp);
			return ;
		}
	}
	g_status = launch_exec(exec_blocks, builtin, ptr_my_envp);
	return ;
}
