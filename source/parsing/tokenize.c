/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:06:19 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/17 20:13:23 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_add_word_token(t_list **tokens, t_tok *tok, char **line);

static void	_add_space_token(t_list **tokens, t_tok *tok, char **line);

static void	_add_operator_token(t_list **tokens, t_tok *tok, char **line);

/*static t_tok	*_get_next_tok(char **line);

static t_tok	*_extract_token(char **line, int i, int has_quote[2]);

static void		_build_wd_tok(t_tok *tok, char **line, int i, int has_quote[2]);

static void		_build_operator_tok(t_tok *tok, char **line, int i);
*/
int	tokenize(char *line, t_list **tokens)
{
	t_tok	*tok;
	char	*spec_chars;
	
	spec_chars = " <>|'\"";
	while (*line)
	{
		tok = (t_tok *)malloc(sizeof(t_tok));
		if (tok == NULL)
			my_exit("Malloc error in parsing: tokenize\n", EXIT_FAILURE);
		if (ind_in_set(*line, spec_chars) == -1)
			_add_word_token(tokens, tok, &line);
		else if (*line == '\'' || *line == '"')
			;
			//_add_quoted_word_tok(tokens, &line);
		else if (*line == ' ')
			_add_space_token(tokens, tok, &line);
		else
			_add_operator_token(tokens, tok, &line);
	}
	return (0);
}

static void	_add_word_token(t_list **tokens, t_tok *tok, char **line)
{		
	char	*spec_chars = " <>|'\"";
	t_list	*token;
	int		i;

	i = 0;
	while ((*line)[i] && ind_in_set((*line)[i], spec_chars) == -1)
		i++;
	tok -> type = word;
	tok -> str = (char *)malloc(i * sizeof(char) + 1);
	if (tok -> str == NULL)
		my_exit("Malloc error in parsing: add_word_token\n", EXIT_FAILURE);
	ft_memcpy(tok -> str, *line, i);
	tok -> str[i] = '\0';
	tok -> len = i;
	(*line) += i;
	token = ft_lstnew((void *) tok);
	if (token == NULL)
		my_exit("Error in parsing: lst_new\n", EXIT_FAILURE);
	ft_lstadd_back(tokens, token);
	return ;
}

static void	_add_space_token(t_list **tokens, t_tok *tok, char **line)
{		
	t_list	*token;
	
	while (**line && is_space(**line))
		(*line)++;
	tok -> type = space;
	tok -> str = NULL;
	tok -> len = 0;
	token = ft_lstnew((void *) tok);
	if (token == NULL)
		my_exit("Error in parsing: lst_new\n", EXIT_FAILURE);
	ft_lstadd_back(tokens, token);
	return ;
}

static void	_add_operator_token(t_list **tokens, t_tok *tok, char **line)
{		
	t_list	*token;
	
	tok -> type = op;
	tok -> str = (char *)malloc(2 * sizeof(char) + 1);
	if (tok -> str == NULL)
		my_exit("Malloc error in parsing:\
			   	build operator token", EXIT_FAILURE);
	tok -> str[1] = '\0';
	tok -> str[2] = '\0';
	tok -> str[0] = **line;
	tok -> len = 1;
	(*line) += 1;
	if (**line == *(*line - 1) && *(*line - 1) != '|')
	{
		tok -> str[1] = **line;
		tok -> len += 1;
		(*line) += 1;
	}
	token = ft_lstnew((void *) tok);
	if (token == NULL)
		my_exit("Error in parsing: lst_new\n", EXIT_FAILURE);
	ft_lstadd_back(tokens, token);
	return ;
}
/*
static t_tok	*_extract_token(char **line, int i, int has_quote[2])
{
	t_tok	*tok;

	tok = (t_tok *)malloc(sizeof(t_tok));
	if (tok == NULL)
		my_exit("Malloc error in parsing extract_token\n", EXIT_FAILURE);
	if (i > 0)
		_build_wd_tok(tok, line, i, has_quote);
	else
		_build_operator_tok(tok, line, i);
	return (tok);
}*/
/*
static void	_build_wd_tok(t_tok *tok, char **line, int i, int has_quote[2])
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
*/
/*
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
}*/
