/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:06:01 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/17 15:38:30 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_process_wordq(t_tok *tok);

/* 
wordq is a string token containing one or several '' pairs
wordqq is a string containing one or several "" pairs and 0 or several '' pairs
*/
void	process_quotes(t_list **ptr_tokens)
{
	t_list	*tokens;
	t_tok	*tok;

	tokens = *ptr_tokens;
	while (tokens)
	{
		tok = (t_tok *)(tokens -> content);
		if (tok -> type == wordq)
			_process_wordq(tok);
		else if (tok -> type == wordqq)
			;
		tokens = tokens -> next;
	}
	return ;
}

static void	_process_wordq(t_tok *tok)
{
	char	*str;
	char	*str_out;
	char	*str_out_cpy;
	int		n_sgl_quote_pairs;

	str = tok -> str;
	n_sgl_quote_pairs = num_sgl_quote_pairs(str);
	str_out = (char *)malloc(tok -> len - n_sgl_quote_pairs * 2 + 1);
	if (str_out == NULL)
		my_exit("Malloc error in process_wordq\n", EXIT_FAILURE);
	str_out_cpy = str_out;
	while (*str)
	{
		if (*str != '\'')
			*str_out_cpy++ = *str;
		str++;
	}
	*str_out_cpy = '\0';
	free(tok -> str);
	tok -> str = str_out;
	tok -> len = tok -> len - n_sgl_quote_pairs * 2;
	tok -> type = word;
	return ;
}
