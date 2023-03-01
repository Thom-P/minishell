/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:47:32 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/01 16:09:31 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_line(t_list *exec_blocks, char ***ptr_my_envp)
{
	//temporary action: print the content of the exec blocks
	ft_lstiter(exec_blocks, &_print_block);
	printf("\n");
	
	//see the readme file

	//Temporary builtin test (Thomas)
	t_block	*block = exec_blocks -> content;
	int	ac = block -> n_arg;
	char **av = block -> cmd_args;
	if (ft_strncmp(av[0], "exit", 5) == 0)
		b_exit(ac, av);
	if (ft_strncmp(av[0], "env", 4) == 0)
		b_env(ac, av, *ptr_my_envp);
	if (ft_strncmp(av[0], "export", 7) == 0)
		b_export(ac, av, ptr_my_envp);
	if (ft_strncmp(av[0], "unset", 6) == 0)
		b_unset(ac, av, ptr_my_envp);

	return ;
}
