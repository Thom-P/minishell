/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:56:43 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/01 16:17:09 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

void	b_exit(int ac, char **av)
{
	if (ac > 2)
		printf("jmsh: exit: too many arguments\n");
	if (ac == 1)
		exit(g_status);
	if (0) //(_is_not_only_num(av[1]))
	{
		printf("jmsh: exit: %s: numeric argument required\n", av[1]);
		exit(255);
	}
	else 
		exit(ft_atoi(av[1]));
	return ;
}


