/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:06:19 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/15 15:13:55 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_tok	*_get_next_tok(char **line);

static t_tok	*_extract_token(char **line, int i, int has_quote[2]);

static void		_build_word_tok(t_tok *tok, char **line, int i, int has_quote[2]);

static void		_build_operator_tok(t_tok *tok, char **line, int i);

int	tokenize(char *line, t_list **tokens)
{
	t_list	*token;

	while (*line)
	{
		while (is_space(*line))
			line++;
		if (*line != 0)
		{	
			token = ft_lstnew((void *)_get_next_tok(&line));
			if (token == NULL)
				my_exit("Error in parsing: lst_new\n", EXIT_FAILURE);
			ft_lstadd_back(tokens, token);
		}
	}
	return (0);
}

//keep including chars while not special or within quote
//has_quote[0] to record if has single quotes
//has_quote[1] to record if has dbl quotes
static t_tok	*_get_next_tok(char **line)
{
	int		i;
	int		in_quote;
	int		has_quote[2];

	i = 0;
	in_quote = 0;
	has_quote[0] = 0;
	has_quote[1] = 0;
	while ((*line)[i] && (in_quote || ind_in_set((*line)[i], " <>|") == -1))
	{
		if ((*line)[i] != '\'' && (*line)[i] != '"')
		{
			i++;
			continue ;
		}
		if ((*line)[i] == '"')
			has_quote[1] = 1;
		else
			has_quote[0] = 1;
		if (in_quote == 0)
			in_quote = (*line)[i];
		else if (in_quote == (*line)[i++])
			in_quote = 0;
	}
	return (_extract_token(line, i, has_quote));
}

static t_tok	*_extract_token(char **line, int i, int has_quote[2])
{
	t_tok	*tok;

	tok = (t_tok *)malloc(sizeof(t_tok));
	if (tok == NULL)
		my_exit("Malloc error in parsing extract_token\n", EXIT_FAILURE);
	if (i > 0)
		_build_word_tok(tok, line, i, has_quote);
	else
		_build_operator_tok(tok, line, i);
	return (tok);
}

static void	_build_word_tok(t_tok *tok, char **line, int i, int has_quote[2])
{
	if (has_quote[1])
		tok -> type = wordqq;
	else if (has_quote[0])
		tok -> type = wordq;
	else
		tok -> type = word;
	tok -> str = (char *)malloc(i * sizeof(char) + 1);
	if (tok -> str == NULL)
		my_exit("Malloc error in parsing: build_word_token\n", EXIT_FAILURE);
	ft_memcpy(tok -> str, *line, i);
	tok -> str[i] = '\0';
	tok -> len = i;
	(*line) += i;
	return ;
}

static void	_build_operator_tok(t_tok *tok, char **line, int i)
{	
	tok -> type = op;
	tok -> str = (char *)malloc(2 * sizeof(char) + 1);
	if (tok -> str == NULL)
		my_exit("Malloc error in parsing:\
			   	build operator token", EXIT_FAILURE);
	tok -> str[1] = '\0';
	tok -> str[2] = '\0';
	tok -> str[0] = (*line)[i];
	tok -> len = 1;
	(*line) += 1;
	if ((*line)[i] == (*line)[i - 1] && (*line)[i - 1] != '|')
	{
		tok -> str[1] = (*line)[i];
		tok -> len += 1;
		(*line) += 1;
	}
	return ;
}
