/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:07:18 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/07 14:30:21 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static void	_update_oldpwd_env(char *old_pwd, char ***ptr_my_env);

static void	_update_pwd_env(char *pwd, char ***ptr_my_env);

int	b_cd(int ac, char **av, char ***ptr_my_env)
{
	int		exit_status;
	char	*old_pwd;
	char	*pwd;

	exit_status = 0;
	if (ac == 1)
		return (exit_status);
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		my_exit("getcwd error in b_cd\n", EXIT_FAILURE);
	exit_status = chdir(av[1]);
	if (exit_status != 0)
	{
		free(old_pwd);
		ft_printf(2, "jmsh: cd: %s: ", av[1]);
		perror("");
		return (1);
	}
	_update_oldpwd_env(old_pwd, ptr_my_env);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		my_exit("getcwd error in b_cd\n", EXIT_FAILURE);
	_update_pwd_env(pwd, ptr_my_env);
	return (exit_status);
}

static void	_update_oldpwd_env(char *old_pwd, char ***ptr_my_env)
{
	char	*av_eff[3];

	av_eff[0] = "export";
	av_eff[1] = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	if (av_eff[1] == NULL)
		my_exit("malloc err in strjoin, _update_old_pwd, b_cd\n", EXIT_FAILURE);
	av_eff[2] = NULL;
	b_export(2, av_eff, ptr_my_env);
	free(av_eff[1]);
	return ;
}

static void	_update_pwd_env(char *pwd, char ***ptr_my_env)
{
	char	*av_eff[3];

	av_eff[0] = "export";
	av_eff[1] = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (av_eff[1] == NULL)
		my_exit("malloc err in strjoin, _update_old_pwd, b_cd\n", EXIT_FAILURE);
	av_eff[2] = NULL;
	b_export(2, av_eff, ptr_my_env);
	free(av_eff[1]);
	return ;
}
