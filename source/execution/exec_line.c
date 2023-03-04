/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:47:32 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/04 21:35:51 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	_get_index_builtin(char *cmd, char *names[N_BUILTIN]);

void	exec_line(t_list *exec_blocks, char ***ptr_my_envp, t_builtin *builtin)
{
	int		ac;
	char	**av;
	int		ind_built;

	ac = ((t_block *)exec_blocks -> content)-> n_arg;
	av = ((t_block *)exec_blocks -> content)-> cmd_args;
	
	//temporary action: print the content of the exec blocks
	//ft_lstiter(exec_blocks, &_print_block);
	//printf("\n");
	
	//see the readme file

	// Case where only one command and builtin
	if (exec_blocks -> next == NULL)
	{
		ind_built = _get_index_builtin(av[0], builtin -> names);
		if (ind_built != -1)
		{	
			g_status = builtin -> f_ptr[ind_built](ac, av, ptr_my_envp);
			return ;
		}
	}
	printf("Not a builtin\n");
	g_status = 0;

	/*if (ft_strncmp(av[0], "echo", 5) == 0)
		g_status = b_echo(ac, av, ptr_my_envp);
	if (ft_strncmp(av[0], "cd", 3) == 0)
		g_status = b_cd(ac, av, ptr_my_envp);
	if (ft_strncmp(av[0], "pwd", 4) == 0)
		g_status = b_pwd(ac, av, ptr_my_envp);
	if (ft_strncmp(av[0], "export", 7) == 0)
		g_status = b_export(ac, av, ptr_my_envp);
	if (ft_strncmp(av[0], "unset", 6) == 0)
		g_status = b_unset(ac, av, ptr_my_envp);
	if (ft_strncmp(av[0], "env", 4) == 0)
		g_status = b_env(ac, av, ptr_my_envp);
	if (ft_strncmp(av[0], "exit", 5) == 0)
		g_status = b_exit(ac, av, ptr_my_envp);*/
	return ;
}

// returns index of bultin in list below or -1 if not a builtin
static int	_get_index_builtin(char *cmd, char *names[N_BUILTIN])
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
