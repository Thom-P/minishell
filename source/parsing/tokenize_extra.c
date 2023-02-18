/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:44:35 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/18 12:30:56 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_var_token(t_list **tokens, char **line)
{		
	char	*spec_chars = " $<>|'\"";
	int		i;
	t_tok	*tok;

	i = 0;
	while ((*line)[i + 1] && ind_in_set((*line)[i + 1], spec_chars) == -1)
		i++;
	new_token(tokens, &tok);
	if (i == 0)
		build_word_tok(tok, line, 1);
	else
		build_var_tok(tok, line, i);
	return ;
}



/*
void	add_dbl_qword_tokens(t_list **tokens, char **line)
{		
	char	*var_delim = " '\"";
	(*line += 1);
	while (**line != '"')
	{
		if (**line == '$' && *(*line + 1) != '"' && (*line +1) )
	}

	i = 0;
	(*line) += 1;
	while ((*line)[i] && (*line)[i] != '\'')
		i++;
	if (i > 0)
	{
		new_token(tokens, &tok);
		build_word_tok(tok, line, i);
	}
	(*line) += 1;
	return ;
}

void	add_dbl_qword_tokens(t_list **tokens, char **line)
{		
	t_tok	*tok;
	int		i;

	i = 0;
	(*line) += 1;
	while ((*line)[i] && (*line)[i] != '\'')
		i++;
	if (i > 0)
	{
		new_token(tokens, &tok);
		build_word_tok(tok, line, i);
	}
	(*line) += 1;
	return ;
}
*/

