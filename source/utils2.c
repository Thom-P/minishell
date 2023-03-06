/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:27:54 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/06 17:30:18 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static char	*_get_updated_shlvl(char *old_str);

void	incr_shell_lvl(char **my_envp)
{
	char	*str;

	while (*my_envp)
	{
		if (ft_strncmp(*my_envp, "SHLVL=", 6) != 0)
		{
			my_envp++;
			continue ;
		}
		str = _get_updated_shlvl(*my_envp);
		free(*my_envp);
		*my_envp = str;
		break ;
	}
	return ;
}

static char	*_get_updated_shlvl(char *old_str)
{
	int		old_lvl;
	char	*new_lvl;
	char	*new_str;

	old_lvl = ft_atoi(&old_str[6]);
	new_lvl = ft_itoa(old_lvl + 1);
	if (new_lvl == NULL)
		my_exit("Malloc error in get_updated_shlvl\n", EXIT_FAILURE);
	new_str = ft_strjoin("SHLVL=", new_lvl);
	if (new_str == NULL)
		my_exit("Malloc error in get_updated_shlvl\n", EXIT_FAILURE);
	free(new_lvl);
	return (new_str);
}

void	print_jmsh_logo(void)
{
	char	*logo;

	logo = "\n\033[1;34m"
		"      _                        __  __ _ ____  _          _ _ \n"
		"     | | ___  __ _ _ __       |  \\/  (_) ___|| |__   ___| | |\n"
		"  _  | |/ _ \\/ _` | '_ \\ _____| |\\/| | \\___ \\| '_ \\ / _ \\ | |\n"
		" | |_| |  __/ (_| | | | |_____| |  | | |___) | | | |  __/ | |\n"
		"  \\___/ \\___|\\__,_|_| |_|     |_|  |_|_|____/|_| |_|\\___|_|_|\n"
		"\033[0m\n"
		"\n";
	printf("%s\n", logo);
	return ;
}
