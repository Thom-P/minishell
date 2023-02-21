/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:48:24 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/21 16:12:11 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_print_token(void *tok);

int	parse_line(char *line, t_list **ptr_exec_block, char **my_envp)
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
	//ft_lstiter(tokens, _print_token);
	//printf("\n");
	expand_variables(tokens, my_envp);
	//printf("After var exp:\n");
	//ft_lstiter(tokens, _print_token);
	//printf("\n");
	merge_word_toks(tokens);
	//printf("After word merge:\n");
	//ft_lstiter(tokens, _print_token);
	//printf("\n");
	remove_space_toks(&tokens);
	//printf("After space removal:\n");
	//ft_lstiter(tokens, _print_token);
	//printf("\n");

	if (verify_tokens(&tokens) == -1)
		return (-1);
	ft_lstiter(tokens, _print_token);
	printf("\n");
	build_exec_blocks(tokens, ptr_exec_block);
	ft_lstclear(&tokens, &free_token);
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
