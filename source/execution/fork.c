/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:17:32 by nadel-be          #+#    #+#             */
/*   Updated: 2023/03/02 17:15:40 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	fork_init(t_exec *exec, t_block *blocks, int n, char **my_env)
{
	exec->pid[n] = fork();
	if (exec->pid[n] == -1)
	{
		return ;
	}
	if (exec->pid[n] == 0)
		child(exec, blocks, my_env, n);
}
