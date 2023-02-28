/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:08:02 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/28 15:07:29 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static void	_add_env(char *arg, int ind_equal, char ***ptr_my_envp);

int	export(int ac, char **av, char ***ptr_my_envp)
{
	int	ind_equal;

	if (ac == 1)
	{
		//print_export();
		return (EXIT_SUCCESS);
	}
	while (*av)	
	{
		if ((*av)[0] == '?' || (*av)[0] == '=' || (*av)[0] == '-')
		{	
			printf("export: %s: not a valid identifier\n", *av);
			return (EXIT_FAILURE);
		}
		ind_equal = ind_in_set('=', *av);
		if (ind_equal > 0)
			_add_env(*av, ind_equal, ptr_my_envp);
		av++;
	}
	return (EXIT_SUCCESS);
}

static void _add_env(char *arg, int ind_equal, char ***ptr_my_envp)
{
	int		new_env_size;
	char	**my_new_envp;
	char 	*new_var;
	int		i;

	(void) ind_equal;
	/*
	
	if (is_already_defined(arg, ind_equal, *ptr_my_envp))
	{	
		_replace_var(arg, ind_equal, *ptr_my_envp);
		return ;
	}
	*/
	new_env_size = get_env_size(*ptr_my_envp) + 1;
	my_new_envp = (char **)malloc(sizeof(char *) * (new_env_size + 1));
	if (my_new_envp == NULL)
		my_exit("Malloc error in export: _add_env\n", EXIT_FAILURE);
	i = 0;
	while (i < (new_env_size - 1))
	{	
		my_new_envp[i] = (*ptr_my_envp)[i];
		i++;
	}
	new_var = ft_strdup(arg);
	if (new_var == NULL)
		my_exit("Malloc error in export: strdup\n", EXIT_FAILURE);
	my_new_envp[i++] = new_var;
	my_new_envp[i] = NULL;
	free(*ptr_my_envp);
	*ptr_my_envp = my_new_envp;
	return ;
}

/*static int is_already_defined(char *arg, int ind_equal, char **my_envp)
{

}
*/
