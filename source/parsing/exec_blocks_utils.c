/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_blocks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:47:54 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/22 16:03:32 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    new_exec_block(t_list **exec_blocks, t_block **ptr_block, int n_redir, int n_arg)
{
	t_list  *exec_block;
	t_block	*block;

	block = (t_block *)malloc(sizeof(t_block));
	if (block == NULL)
		my_exit("Malloc error in new_exec_block\n", EXIT_FAILURE);
	*ptr_block = block;
	block -> n_redir = n_redir;
	block -> n_arg = n_arg;
	block -> redir = (enum e_redir *)ft_calloc(n_redir, sizeof(enum e_redir));
	if (block -> redir == NULL)
		my_exit("Malloc error in new_exec_block\n", EXIT_FAILURE);
	block -> files = (char **)ft_calloc(n_redir + 1, sizeof(char *));
	if (block -> files == NULL)
		my_exit("Malloc error in new_exec_block\n", EXIT_FAILURE);
	block -> cmd_args = (char **)ft_calloc(n_arg + 1, sizeof(char *));
	if (block -> cmd_args == NULL)
		my_exit("Malloc error in new_exec_block\n", EXIT_FAILURE);
	exec_block = ft_lstnew((void *)block);
	if (exec_block == NULL)
		my_exit("Malloc error in new_exec_block: lst_new\n", EXIT_FAILURE);
	ft_lstadd_back(exec_blocks, exec_block);
	return ;
}

void    free_block(void *tmp_block)
{
	t_block *block;

	block = (t_block *)tmp_block;
	free(block -> redir);
	free_tab(block -> files);
	free_tab(block -> cmd_args);
	free((t_tok *)block);
	return ;
}

void	free_tab(char **tab)
{
	char	**tab_cpy;

	tab_cpy = tab;
	if (tab == NULL)
		return ;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(tab_cpy);
	return ;
}
