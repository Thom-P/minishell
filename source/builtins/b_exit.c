/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:56:43 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/07 10:22:44 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static int	_is_only_num(char *str);

int	b_exit(int ac, char **av, char ***ptr_my_envp)
{
	(void) ptr_my_envp;
	if (ac > 2)
	{	
		printf("jmsh: exit: too many arguments\n");
		return (1);
	}
	if (ac == 1)
		my_exit("exit\n", g_status);
	if (!_is_only_num(av[1]))
	{
		printf("exit\njmsh: exit: %s: numeric argument required\n", av[1]);
		exit(255);
	}
	else
		my_exit("exit\n", ft_atoi(av[1]));
	return (0);
}

static int	_is_only_num(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
