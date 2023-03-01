/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:00:27 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/01 11:03:02 by tplanes          ###   ########.fr       */
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

int	is_var_name_legal(char *str)
{
	if (str[0] == '\0' || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}
