/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:47:32 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/02 18:11:36 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_exec_struct(t_exec *exec, t_list *exec_blocks, char **my_env)
{
	int	nb_blocks;
	int	i;

	i = -1;
	nb_blocks = ft_lstsize(exec_blocks);
	exec->nb_pipes = nb_blocks - 1;
	exec->nb_cmd = nb_blocks;
	exec->fd = ft_calloc(sizeof(*exec->fd), exec->nb_pipes);
	if (exec->fd == NULL)
		return ;
	exec->pid = ft_calloc(sizeof(exec->pid), exec->nb_cmd);
	if (exec->pid == NULL)
		return ;
	while (my_env[++i])
	{
		if (ft_strnstr(my_env[i],
				"PATH=", ft_strlen(my_env[i])) != NULL)
			exec->path = ft_split(&my_env[i][5], ':');
	}
}

void	free_tab_path(t_exec *exec)
{
	int	i;

	i = -1;
	while (exec->path[++i])
		free(exec->path[i]);
	free(exec->path);
}

int	launch_exec(t_list *exec_blocks, char ***my_env)
{
	int		n;
	t_exec	exec;

	init_exec_struct(&exec, exec_blocks, *my_env);
	if (exec.nb_pipes > 0)
		pipe_init(&exec, exec.fd);
	n = -1;
	while (++n < exec.nb_cmd)
	{
		fork_init(&exec, (t_block *)(exec_blocks -> content), n, *my_env);
		exec_blocks = exec_blocks->next;
	}
	if (exec.nb_pipes > 0)
		close_pipe(&exec);
	// close(exec.fd_in);
	// close(exec.fd_out);
	// waitpid(-1, &g_status, 0);
	waitpid(-1, NULL, 0);
	free_tab_path(&exec);
	free(exec.pid);
	return (0);
}

void	exec_line(t_list *exec_blocks, char ***ptr_my_envp)
{
	//temporary action: print the content of the exec blocks
	ft_lstiter(exec_blocks, &_print_block);
	printf("\n");
	
	//see the readme file

	//Temporary builtin test (Thomas)
	// t_block	*block = exec_blocks -> content;
	// int	ac = block -> n_arg;
	// char **av = block -> cmd_args;
	// if (ft_strncmp(av[0], "exit", 5) == 0)
	// 	my_exit("", EXIT_SUCCESS);
	// if (ft_strncmp(av[0], "env", 4) == 0)
	// 	my_env(ac, av, *ptr_my_envp);
	// if (ft_strncmp(av[0], "export", 7) == 0)
	// 	my_export(ac, av, ptr_my_envp);
	launch_exec(exec_blocks, ptr_my_envp);
	return ;
}
