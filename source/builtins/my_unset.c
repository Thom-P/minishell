/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:46:08 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/28 19:14:40 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static void	_remove_env(char *arg, char ***ptr_my_envp);

int	my_unset(int ac, char **av, char ***ptr_my_envp)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (ac == 1)
		return (exit_status);
	while (*av)	
	{
		if ((*av)[0] == '?' || (*av)[0] == '=' || (*av)[0] == '-') //MAKE SURE THAT NO EQUAL
		{	
			printf("unset: %s: not a valid identifier\n", *av);
			exit_status = EXIT_FAILURE;
			av++;
			continue ;
		}
		if (_is_var_in_env(*av, *ptr_my_envp))
			_add_env(*av, ptr_my_envp);
		av++;
	}
	return (exit_status);
}

static void _add_env(char *arg, char ***ptr_my_envp)
{
	int		new_env_size;
	char	**my_new_envp;
	char 	*new_var;
	int		i;

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

static int _ind_var_in_env(char *var, char **my_envp)
{
	int	ind;
	int	var_len;

	ind = -1;
	var_len = ft_strlen(var);
	while (*my_envp)
	{
		if (ft_strncmp(*my_envp, var, var_len) == 0 && *my_envp[var_len] == '=')
		{	
			free(*my_envp);
			*my_envp = ft_strdup(arg);
			if (*my_envp == NULL)
				my_exit("Malloc error in _repl_if_already_def\n", EXIT_FAILURE);
			return (1);
		}
		my_envp++;
	}
	return (ind);
}

/*static void	_print_export(char **my_envp);
{
	
}*/
