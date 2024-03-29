/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:04:54 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/02 13:40:03 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

int	b_echo(int ac, char **av, char ***ptr_my_envp)
{
	int	flag_nl;

	(void) ptr_my_envp;
	flag_nl = 1;
	if (ac == 1)
	{	
		printf("\n");
		return (0);
	}
	av++;
	if (ft_strncmp(*av, "-n", 3) == 0)
	{	
		flag_nl = 0;
		av++;
	}
	if (*av)
		ft_printf(STDOUT_FILENO, "%s", *av++);
	while (*av)
		ft_printf(STDOUT_FILENO, " %s", *av++);
	if (flag_nl)
		printf("\n");
	return (0);
}
