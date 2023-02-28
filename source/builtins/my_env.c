/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:41:04 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/28 16:41:16 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

//SHOULD MODIFY _= to fit bash ?

int	my_env(int ac, char **av, char **my_envp)
{
	(void) av;
	if (ac != 1)
	{
		printf("env: illegal option or argument\n");
		return (EXIT_FAILURE);
	}
	while (*my_envp)
	{
		printf("%s\n", *my_envp);
		my_envp++;
	}
	return (EXIT_SUCCESS);
}
