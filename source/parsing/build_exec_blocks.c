/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exec_blocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:00:19 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/21 17:50:33 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	build_exec_blocks(t_list *tokens, t_list **ptr_exec_blocks)
{
	int	n_redir;
	int n_arg;

	while (*tokens)
	{
		n_redir = get_num_redir(tokens);
		n_args = get_num_args(tokens);
		_add_exec_block(ptr_exec_blocks, &tokens, n_redir, n_arg);
	}
}

static void	_add_exec_block(t_list **ptr_exec_block, t_list **ptr_tokens, int n_redir, int n_arg)
{
	t_block	*block;
	t_list	*token;
	t_tok	*tok;

	
	new_exec_block(ptr_exec_block, &block, n_redir, n_arg);
	token = *ptr_tokens;
	while (token)
	{
		tok = (t_tok *)token -> content;
		if (tok -> type == op && tok -> str == '|')
		{	
			token = token -> next;
			break ;
		}
		_copy_token_data(block, tok);
		token = token -> next;
	}
	*ptr_tokens = token;
}

static void	_copy_token_data(block, tok)
{
	if (tok -> type == op & tok -> str = '<')
		block -> 
	return ;
}

void    new_exec_block(t_list **exec_blocks, t_block **block, n_redir, n_arg)
{
	t_list  *exec_block;

	*block = (t_block *)malloc(sizeof(t_block));
	if (*block == NULL)
		my_exit("Malloc error in new_exec_block\n", EXIT_FAILURE);
	block -> n_redir = n_redir;
	block -> n_arg = n_redir;
	block -> redir = (enum e_redir *)malloc(sizeof(enum e_redir) * n_redir);
	if (block -> redir == NULL)
		my_exit("Malloc error in new_exec_block\n", EXIT_FAILURE);
	block -> file_array = (char **)malloc(sizeof(char *) * n_redir + 1);
	if (block -> file_array == NULL)
		my_exit("Malloc error in new_exec_block\n", EXIT_FAILURE);
	block -> cmd_args = (char **)malloc(sizeof(char *) * n_arg + 1);
	if (block -> cmd_args == NULL)
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
