/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:48:24 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/24 15:16:33 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_print_token(void *tok);

static void	_print_block(void *block);

int	parse_line(char *line, t_list **exec_blocks, char **my_envp)
{
	t_list	*tokens;

	tokens = NULL;
	printf("Parsing: %s\n", line);
	if (is_only_space(line))
		return (-1);
	if (odd_num_quote(line))
	{	
		printf("Error: missing quote\n");
		return (-1);
	}
	tokenize(line, &tokens);
	//printf("Before var exp:\n");
	//ft_lstiter(tokens, &_print_token);
	//printf("\n");
	expand_variables(tokens, my_envp);
	//printf("After var exp:\n");
	//ft_lstiter(tokens, &_print_token);
	//printf("\n");
	merge_word_toks(tokens);
	//printf("After word merge:\n");
	//ft_lstiter(tokens, &_print_token);
	//printf("\n");
	remove_space_toks(&tokens);
	//printf("After space removal:\n");
	//ft_lstiter(tokens, &_print_token);
	//printf("\n");
	if (verify_tokens(&tokens) == -1)
		return (-1);
	ft_lstiter(tokens, &_print_token);
	printf("\n\n");
	build_exec_blocks(tokens, exec_blocks);
	ft_lstiter(*exec_blocks, &_print_block);
	printf("\n");
	ft_lstclear(&tokens, &free_token);
	ft_lstclear(exec_blocks, &free_block);
	return (0);
}

// for debug only
static void	_print_token(void *tok)
{
	char	*type;

	switch (((t_tok *)tok)-> type)
	{
		case word:
		type = "wd";
		break;
		case space:
		type = "sp";
		break;
		case op:
		type = "op";
		break;
		case var:
		type = "vr";
		break;
		default:
		type = "??";
	}
	printf("(%s:%s:%i) ", type, ((t_tok *)tok)-> str, ((t_tok *)tok)-> len);
	return ;
}

// for debug only
static void	_print_block(void *block_tmp)
{
	t_block	*block;
	char	**files;
	char	**cmd_args;
	char	*redir;
	int	i;	
	
	block = (t_block *) block_tmp;
	files = block -> files;
	printf("BLOCK\n");
	printf("%i redirs:\n", block -> n_redir);
	i = 0;
	while (files[i])
	{
		switch(block -> redir[i])
		{
			case in:
			redir = "in";
			break;
			case out:
			redir = "out";
			break;
			case append:
			redir = "append";
			break;
			default:
			redir = "??";
		}
		printf("%s: '%s'\n", redir, files[i]);
		i++;
	}
	//printf("\n");
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
