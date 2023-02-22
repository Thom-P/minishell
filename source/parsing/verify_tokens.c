/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:06:29 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/22 16:21:02 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	_first_tok_is_pipe(t_list **ptr_tokens);

static int	_two_successive_toks_are_op(t_list **ptr_tokens, char *last_op);

static int	_last_tok_is_op(t_list **ptr_tokens, int last_op);

/* 
Returns error if:
- first token is pipe
- two successive tokens are operators (not that bash authorizes <>, not jmsh)
- last token is any operator
*/
int	verify_tokens(t_list **ptr_tokens)
{
	char	last_op;

	last_op = 0;
	if (_first_tok_is_pipe(ptr_tokens))
		return (-1);
	if (_two_successive_toks_are_op(ptr_tokens, &last_op))
		return (-1);
	if (_last_tok_is_op(ptr_tokens, last_op))
		return (-1);
	return (0);
}

static int	_first_tok_is_pipe(t_list **ptr_tokens)
{
	t_tok	*tok;

	tok = (t_tok *)((*ptr_tokens)-> content);
	if (tok -> type == op && tok -> str[0] == '|')
	{	
		printf("jmsh: syntax error near unexpected token `|'\n");
		ft_lstclear(ptr_tokens, &free_token);
		return (1);
	}
	return (0);
}

//except | <file that is ok
static int	_two_successive_toks_are_op(t_list **ptr_tokens, char *last_op)
{
	t_list	*tokens;
	t_tok	*tok;

	tokens = *ptr_tokens;
	while (tokens)
	{
		tok = (t_tok *)tokens -> content;
		if (tok -> type == op)
		{
			if (*last_op && (*last_op != '|' || *(tok-> str) == '|'))
			{
				printf("jmsh: syntax error near unexpected token `%s'\n",
					tok -> str);
				ft_lstclear(ptr_tokens, &free_token);
				return (1);
			}
			*last_op = *(tok -> str);
		}
		else
			*last_op = 0;
		tokens = tokens -> next;
	}
	return (0);
}

static int	_last_tok_is_op(t_list **ptr_tokens, int last_op)
{
	if (last_op)
	{	
		printf("jmsh: syntax error near unexpected token `newline'\n");
		ft_lstclear(ptr_tokens, &free_token);
		return (1);
	}
	return (0);
}
