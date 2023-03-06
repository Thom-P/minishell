/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:53:28 by nadel-be          #+#    #+#             */
/*   Updated: 2023/03/06 16:40:51 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_cmd(t_exec *exec, char *cmd)
{
	char	*res;

	res = ft_calloc(sizeof(*res), 1);
	if (res == NULL)
		my_exit("malloc error in find_cmd\n", EXIT_FAILURE);
	res = access_cmd(exec, cmd);
	if (res == NULL)
	{
		g_status = 127;
		ft_printf(STDERR_FILENO, "jmsh: %s: command not found\n", cmd);
		my_exit("", g_status);
	}
	return (res);
}
