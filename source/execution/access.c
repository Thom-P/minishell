/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:08:53 by nadel-be          #+#    #+#             */
/*   Updated: 2023/03/06 16:32:02 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*access_cmd(t_exec *exec, char *cmd)
{
	int		i;
	char	*path_cmd;
	char	*tmp;

	i = -1;
	while (exec->path[++i])
	{
		tmp = ft_strjoin(exec->path[i], "/");
		if (tmp == NULL)
			my_exit("Malloc error in access_cmd\n", EXIT_FAILURE);
		path_cmd = ft_strjoin(tmp, cmd);
		if (path_cmd == NULL)
			my_exit("Malloc error in access_cmd\n", EXIT_FAILURE);
		free(tmp);
		if (access(path_cmd, F_OK) == 0)
			return (path_cmd);
	}
	free(path_cmd);
	return (NULL);
}
