/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:48:24 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/13 16:37:58 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void _print_token(void *tok);

int parse_line(char *line)
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
	ft_lstiter(tokens, _print_token);
	return (0);
}

// for debug
static void _print_token(void *tok)
{
	printf("Token type: %i\n", ((t_tok *)tok)-> type);
	printf("Token val: %s\n", ((t_tok *)tok)-> str);
	printf("Token len: %i\n\n", ((t_tok *)tok)-> len);
	return ;
}