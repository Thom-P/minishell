/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:51:29 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/15 17:45:04 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void _tok_expand(tok)

void expand_variables(t_list **ptr_tokens)
{
	t_list	*tokens;
	t_tok	*tok;

	tokens = *ptr_tokens;	
	while (tokens)
	{
		tok = (t_tok *)(tokens -> content);
		if (tok -> type == wordqq)
			_tok_expand(tok);
		tokens = tokens -> next;
	}	
}

//Looks for "" then $var
static void _tok_expand(t_tok *tok)
{
	char	*str;
	int		len;
	int 	i;

	str = tok -> str;
	len = tok -> len;
	i = 0;
	while (*str && *str"")
	{

	}
}
