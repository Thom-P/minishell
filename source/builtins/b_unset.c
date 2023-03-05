/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:56:02 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/01 15:56:16 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static void	_remove_env(int ind_var, char ***ptr_my_envp);

static int	_ind_var_in_env(char *var, char **my_envp);

int	b_unset(int ac, char **av, char ***ptr_my_envp)
{
	int	exit_status;
	int	ind_var;

	exit_status = EXIT_SUCCESS;
	if (ac == 1)
		return (exit_status);
	av++;
	while (*av)
	{
		ind_var = _ind_var_in_env(*av, *ptr_my_envp);
		if (ind_in_set('=', *av) != -1 || !is_var_name_legal(*av))
		{	
			printf("unset: %s: not a valid identifier\n", *av);
			exit_status = EXIT_FAILURE;
		}
		else if (ind_var != -1)
			_remove_env(ind_var, ptr_my_envp);
		av++;
	}
	return (exit_status);
}

static void	_remove_env(int ind_var, char ***ptr_my_envp)
{
	int		new_env_size;
	char	**my_new_envp;
	int		i;

	new_env_size = get_env_size(*ptr_my_envp) - 1;
	my_new_envp = (char **)malloc(sizeof(char *) * (new_env_size + 1));
	if (my_new_envp == NULL)
		my_exit("Malloc error in export: _remove_env\n", EXIT_FAILURE);
	i = 0;
	while (i < ind_var)
	{	
		my_new_envp[i] = (*ptr_my_envp)[i];
		i++;
	}
	free((*ptr_my_envp)[i]);
	while (i < new_env_size)
	{	
		my_new_envp[i] = (*ptr_my_envp)[i + 1];
		i++;
	}
	my_new_envp[i] = NULL;
	free(*ptr_my_envp);
	*ptr_my_envp = my_new_envp;
	return ;
}

static int	_ind_var_in_env(char *var, char **my_envp)
{
	int	ind;
	int	var_len;

	ind = 0;
	var_len = ft_strlen(var);
	while (my_envp[ind])
	{
		if (ft_strncmp(my_envp[ind], var, var_len) == 0
			&& my_envp[ind][var_len] == '=')
			return (ind);
		ind++;
	}
	return (-1);
}
