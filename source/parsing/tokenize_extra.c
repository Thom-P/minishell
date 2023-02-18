/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:44:35 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/18 15:50:43 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_add_dbl_qword_token(t_list **tokens, char **line);

void	add_var_token(t_list **tokens, char **line)
{		
	char	*spec_chars = " $<>|'\"";
	int		i;
	t_tok	*tok;
	
	new_token(tokens, &tok);
	if ((*line)[1] == '?')
	{	
		build_var_tok(tok, line, 1);
		return ;
	}
	i = 0;
	while ((*line)[i + 1] && ind_in_set((*line)[i + 1], spec_chars) == -1)
		i++;
	if (i == 0)
		build_word_tok(tok, line, 1);
	else
		build_var_tok(tok, line, i);
	return ;
}

void	add_dbl_quote_tokens(t_list **tokens, char **line)
{		
	(*line) += 1;
	while (**line != '"')
	{
		if (**line == '$')
			add_var_token(tokens, line);
		else
			_add_dbl_qword_token(tokens, line);
	}	
	(*line) += 1;
	return ;
}

static void	_add_dbl_qword_token(t_list **tokens, char **line)
{		
	t_tok	*tok;
	int		i;

	i = 0;
	while ((*line)[i] && (*line)[i] != '$' && (*line)[i] != '"')
		i++;
	new_token(tokens, &tok);
	build_word_tok(tok, line, i);
	return ;
}


