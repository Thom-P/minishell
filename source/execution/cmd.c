/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:53:28 by nadel-be          #+#    #+#             */
/*   Updated: 2023/03/06 11:18:37 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_cmd(t_exec *exec, char *cmd)
{
	char	*res;

	res = ft_calloc(sizeof(*res), 1);
	if (res == NULL)
		return (NULL);
	res = access_cmd(exec, cmd);
	return (res);
}
