/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:48:44 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/02 11:00:12 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

int	b_pwd(int ac, char **av, char ***ptr_my_envp)
{
	char	*buf;
	(void) ac;
	(void) av;
	(void) ptr_my_envp;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		my_exit("getcwd alloc error\n", EXIT_FAILURE);
	printf("%s\n", buf);
	free(buf);
	return (EXIT_SUCCESS);
}
