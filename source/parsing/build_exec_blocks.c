/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exec_blocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:00:19 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/21 16:50:30 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	build_exec_blocks(t_list *tokens, t_list **ptr_exec_blocks)
{
	while (*tokens)
		_add_exec_block(ptr_exec_blocks, &tokens);
}

static void	_add_exec_block(t_list **ptr_exec_block, t_list **ptr_tokens)
{
	t_block	*block;
	t_list	*token;
	t_tok	*tok;

	new_exec_block(ptr_exec_block, &block);
	token = *ptr_tokens;
	//build block:
	while (token)
	{
		tok = (t_tok *)token -> content;
		if (tok)	
	
	}
}

void    new_exec_block(t_list **exec_blocks, t_block **block)
{
	t_list  *exec_block;

	*block = (t_block *)malloc(sizeof(t_block));
	if (*block == NULL)
		my_exit("Malloc error in new_exec_block\n", EXIT_FAILURE);
	exec_block = ft_lstnew((void *)(*block));
	if (exec_block == NULL)
		my_exit("Malloc error in new_exec_block: lst_new\n", EXIT_FAILURE);
	ft_lstadd_back(exec_blocks, exec_block);
	return ;
}

void    free_block(void *block)
{
	free(block -> redir);
	free_tab(block -> file_array);
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
