/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:00:27 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/01 10:23:42 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

int	get_env_size(char **my_envp)
{
	int	size;

	size = 0;
	while (my_envp[size])
		size++;
	return (size);
}

int	is_var_name_legal(char *name)
{
	if (name[0] == '\0' || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}
