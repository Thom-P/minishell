/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:41:42 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/01 12:56:51 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static void	_add_env(char *arg, char ***ptr_my_envp);

static int	_repl_if_already_def(char *arg, int ind_equal, char **my_envp);

//static void	_print_export(char **my_envp);

//export without option and name said to be undefined in one man, and just print values in other
int	my_export(int ac, char **av, char ***ptr_my_envp)
{
	int	ind_equal;
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (ac == 1)
	{
		//_print_export(*ptr_my_envp);
		my_env(ac, av, *ptr_my_envp);
		return (EXIT_SUCCESS);
	}
	av++;
	while (*av)	
	{
		ind_equal = ind_in_set('=', *av);
		if (!is_var_name_legal(*av))
		{
			printf("export: %s: not a valid identifier\n", *av);
			exit_status = EXIT_FAILURE;
		}
		else if (ind_equal != -1 && !_repl_if_already_def(*av, ind_equal, *ptr_my_envp))
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

static int _repl_if_already_def(char *arg, int ind_equal, char **my_envp)
{
	while (*my_envp)
	{
		if (ft_strncmp(*my_envp, arg, ind_equal + 1) == 0)
		{	
			free(*my_envp);
			*my_envp = ft_strdup(arg);
			if (*my_envp == NULL)
				my_exit("Malloc error in _repl_if_already_def\n", EXIT_FAILURE);
			return (1);
		}
		my_envp++;
	}
	return (0);
}

/*static void	_print_export(char **my_envp);
{
	
}*/
