/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:55:05 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/02 14:40:03 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

//SHOULD MODIFY _= to fit bash ?

int	b_env(int ac, char **av, char ***ptr_my_envp)
{
	char	**my_envp;

	(void) av;
	my_envp = *ptr_my_envp;
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
