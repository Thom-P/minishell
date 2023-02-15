/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:06:29 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/15 14:10:55 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* 
Returns error if:
- first token is pipe
- two successive tokens are operators (not that bash authorizes <>, not jmsh)
- last token is any operator
*/
int verify_tokens(t_list **ptr_tokens)
{
	t_list	*tokens;
	t_tok 	*tok;
	int		flag_op;

	tokens = *ptr_tokens;
	tok = (t_tok *)tokens -> content;
	if (tok -> type == op && tok -> str[0] == '|')
	{	
		printf("jmsh: syntax error near unexpected token `|'\n");
		ft_lstclear(ptr_tokens, &free_token);
		return (-1);
	}

	flag_op = 0;
	while (tokens)
	{
		tok = (t_tok *)tokens -> content;
		if (tok -> type == op)
		{
			if (flag_op == 1)
			{
				printf("jmsh: syntax error near unexpected token `%s'\n", tok -> str);
				ft_lstclear(ptr_tokens, &free_token);
				return (-1);
			}
			flag_op = 1;
		}
		else
			flag_op = 0;
		tokens = tokens -> next;
	}
	if (flag_op)
	{	
		printf("jmsh: syntax error near unexpected token `newline'\n");
		ft_lstclear(ptr_tokens, &free_token);
		return (-1);
	}
	return (0);
}
