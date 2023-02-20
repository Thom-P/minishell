/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:42:50 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/20 18:36:44 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_merge_word(t_list *token, t_tok *tok_ini);

void	merge_word_toks(t_list *tokens)
{
	t_tok	*tok;
	while (tokens)
	{
		tok = (t_tok *)(tokens -> content);
		if (tok -> type == word)
		{
			_merge_word(tokens, tok);
		}
		tokens = tokens -> next;
	}
}

static void	_merge_word(t_list *token, t_tok *tok_ini)
{
	t_list	*token_tmp;
	t_tok	*tok_next;
	char	*str_tmp;

	while (token -> next)
	{
		tok_next = (t_tok *)(token -> next -> content);
		if (tok_next -> type != word)
			break ;
		str_tmp = ft_strjoin(tok_ini -> str, tok_next -> str);
		if (str_tmp == NULL)
			my_exit("Malloc error in merge word strjoin\n", EXIT_FAILURE);
		free(tok_ini -> str);
		tok_ini -> str = str_tmp;
		tok_ini -> len += tok_next -> len;
		free_token(tok_next);
		token_tmp = token -> next -> next;
		free(token -> next);
		token -> next = token_tmp;
	}
	return ;
}
