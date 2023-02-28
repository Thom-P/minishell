/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:10:55 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/28 13:12:53 by tplanes          ###   ########.fr       */
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
