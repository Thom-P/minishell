/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exec_blocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:00:19 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/22 16:46:59 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_add_exec_block(t_list **exec_blocks, t_list **tokens, int n_redir, int n_arg);

static void	_copy_redir_data(t_block *block, t_tok *tok, char *redir);

static void	_copy_arg_data(t_block *block, t_tok *tok);

void	build_exec_blocks(t_list *tokens, t_list **exec_blocks)
{
	int	n_redir;
	int n_arg;

	while (tokens)
	{
		n_redir = get_num_redir(tokens);
		n_arg = get_num_arg(tokens);
		//printf("n_redir=%i, n_arg=%i\n", n_redir, n_arg);
		//break ;
		_add_exec_block(exec_blocks, &tokens, n_redir, n_arg);
	}
	return ;
}

static void	_add_exec_block(t_list **exec_blocks, t_list **tokens, int n_redir, int n_arg)
{
	t_block	*block;
	t_list	*token;
	t_tok	*tok;
	char	*redir;
	
	new_exec_block(exec_blocks, &block, n_redir, n_arg);
	token = *tokens;
	while (token)
	{
		tok = (t_tok *)token -> content;
		if (tok -> type == op && *(tok -> str) == '|')
		{	
			token = token -> next;
			break ;
		}
		else if (tok -> type == op)
		{	
			redir = tok -> str;
			token = token -> next;
			tok = (t_tok *)token -> content;
			_copy_redir_data(block, tok, redir);
			token = token -> next;
			continue ;
		}
		else
			_copy_arg_data(block, tok);
		token = token -> next;
	}
	*tokens = token;
}

static void	_copy_redir_data(t_block *block, t_tok *tok, char *redir)
{
	char	**files;
	int		i;

	files = block -> files;
	i = 0;
	while (files[i])
		i++;
	if (*redir == '<')
		block -> redir[i] = in;
	else if (redir[0] == '>' && redir[1] == '>')
		block -> redir[i] = append;
	else
		block -> redir[i] = out;
	files[i] = ft_strdup(tok -> str);
	if (files[i] == NULL)
		my_exit("Malloc error in copy_redir_data\n", EXIT_FAILURE);
	return ;
}

static void	_copy_arg_data(t_block *block, t_tok *tok)
{
	char	**cmd_args;
	int		i;

	cmd_args = block -> cmd_args;
	i = 0;
	while (cmd_args[i])
		i++;
	cmd_args[i] = ft_strdup(tok -> str);
	if (cmd_args[i] == NULL)
		my_exit("Malloc error in copy_arg_data\n", EXIT_FAILURE);
	return ;
}
