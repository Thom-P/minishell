/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:06:19 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/18 16:47:27 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_add_word_token(t_list **tokens, char **line);

static void	_add_space_token(t_list **tokens, char **line);

static void	_add_operator_token(t_list **tokens, char **line);

static void	_add_sgl_qword_token(t_list **tokens, char **line);

int	tokenize(char *line, t_list **tokens)
{
	char	*spec_chars;

	spec_chars = " $<>|'\"";
	while (*line)
	{
		if (ind_in_set(*line, spec_chars) == -1)
			_add_word_token(tokens, &line);
		else if (*line == '\'')
			_add_sgl_qword_token(tokens, &line);
		else if (*line == '"')
			add_dbl_quote_tokens(tokens, &line);
		else if (*line == ' ')
			_add_space_token(tokens, &line);
		else if (*line == '$')
			add_var_token(tokens, &line);
		else
			_add_operator_token(tokens, &line);
	}
	return (0);
}

static void	_add_word_token(t_list **tokens, char **line)
{		
	t_tok	*tok;
	char	*spec_chars;
	int		i;

	spec_chars = " $<>|'\"";
	i = 0;
	while ((*line)[i] && ind_in_set((*line)[i], spec_chars) == -1)
		i++;
	new_token(tokens, &tok);
	build_word_tok(tok, line, i);
	return ;
}

//extract word inside the single quotes
//cannot have two successive null words
static void	_add_sgl_qword_token(t_list **tokens, char **line)
{		
	t_tok	*tok;
	int		i;

	i = 0;
	(*line) += 1;
	while ((*line)[i] && (*line)[i] != '\'')
		i++;
	if (i > 0 || !is_last_tok_null_wd(tokens))
	{	
		new_token(tokens, &tok);
		build_word_tok(tok, line, i);
	}
	(*line) += 1;
	return ;
}

static void	_add_space_token(t_list **tokens, char **line)
{		
	t_tok	*tok;

	while (**line && is_space(**line))
		(*line)++;
	new_token(tokens, &tok);
	tok -> type = space;
	tok -> str = NULL;
	tok -> len = 0;
	return ;
}

static void	_add_operator_token(t_list **tokens, char **line)
{		
	t_tok	*tok;

	new_token(tokens, &tok);
	tok -> type = op;
	tok -> str = (char *)malloc(2 * sizeof(char) + 1);
	if (tok -> str == NULL)
		my_exit("Malloc error in parsing: add_operator_token", EXIT_FAILURE);
	tok -> str[1] = '\0';
	tok -> str[2] = '\0';
	tok -> str[0] = **line;
	tok -> len = 1;
	(*line) += 1;
	if (**line == *(*line - 1) && (**line == '<' || **line == '>'))
	{
		tok -> str[1] = **line;
		tok -> len += 1;
		(*line) += 1;
	}
	return ;
}
