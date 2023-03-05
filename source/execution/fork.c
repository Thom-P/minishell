/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:17:32 by nadel-be          #+#    #+#             */
/*   Updated: 2023/03/05 18:26:20 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	fork_init(t_exec *exec, t_block *blocks, t_builtin *builtin,
			char **my_env)
{
	exec->pid[exec->n] = fork();
	if (exec->pid[exec->n] == -1)
	{
		return ;
	}
	if (exec->pid[exec->n] == 0)
		child(exec, blocks, builtin, my_env);
}
