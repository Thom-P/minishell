/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:40:06 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/06 17:29:36 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

void	my_exit(char *msg, int status)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	exit(status);
	return ;
}

void	free_wd_array(char **arr)
{
	char	**arr_cpy;

	arr_cpy = arr;
	if (arr == NULL)
		return ;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(arr_cpy);
	return ;
}

int	ind_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (i);
		i++;
	}
	return (-1);
}

char	**copy_envp(char **envp)
{
	int		size;
	char	**my_envp;

	size = 0;
	while (envp[size])
		size++;
	my_envp = (char **)malloc((size + 1) * sizeof(char *));
	if (my_envp == NULL)
		my_exit("Malloc error in copy_envp\n", EXIT_FAILURE);
	size = 0;
	while (envp[size])
	{	
		my_envp[size] = ft_strdup(envp[size]);
		if (my_envp[size] == NULL)
			my_exit("Malloc error in copy_envp\n", EXIT_FAILURE);
		size++;
	}
	my_envp[size] = NULL;
	return (my_envp);
}

//for debug only
/*
void	_print_block(void *block_tmp)
{
	t_block	*block;
	char	**files;
	char	**cmd_args;
	char	*redir;
	int		i;	

	block = (t_block *) block_tmp;
	files = block -> files;
	printf("BLOCK\n");
	printf("%i redirs:\n", block -> n_redir);
	i = 0;
	while (files[i])
	{
		switch (block -> redir[i])
		{
			case in:
			redir = "in";
			break ;
			case out:
			redir = "out";
			break ;
			case append:
			redir = "append";
			break ;
			default :
			redir = "??";
		}
		printf("%s: '%s'\n", redir, files[i]);
		i++;
	}
	cmd_args = block -> cmd_args;
	printf("%i args:\n", block -> n_arg);
	i = 0;
	while (cmd_args[i])
	{
		printf("%s ", cmd_args[i]);
		i++;
	}
	printf("\n\n");
	return ;
}
*/
