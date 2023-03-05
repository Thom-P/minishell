/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:08:53 by nadel-be          #+#    #+#             */
/*   Updated: 2023/03/02 16:54:21 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*access_cmd(t_exec *exec, char *cmd)
{
	int		i;
	char	*path_cmd;

	i = -1;
	while (exec->path[++i])
	{
		path_cmd = NULL;
		path_cmd = ft_strjoin(exec->path[i], "/");
		path_cmd = ft_strjoin(path_cmd, cmd);
		if (access(path_cmd, F_OK) == 0)
			return (path_cmd);
	}
	return (NULL);
}