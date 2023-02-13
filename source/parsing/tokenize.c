/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:06:19 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/13 16:40:07 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_tok *_get_next_tok(char **line);

int tokenize(char *line, t_list **tokens)
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

static t_tok *_get_next_tok(char **line)
{
	int		i;
	char	*set = " <>|";
	int		in_quote;
	int		has_quote;
	t_tok	*tok;

	tok = (t_tok *)malloc(sizeof(t_tok));
	if (tok == NULL)
		my_exit("Malloc error in parsing: get_next_tok\n", EXIT_FAILURE);
	i = 0;
	in_quote = 0;
	has_quote = 0;
	while ((*line)[i] && (in_quote || ind_in_set((*line)[i],  set) == -1)) //while not spec char 
	{
		if ((*line)[i] != '\'' && (*line)[i] != '"')
		{
			i++;
			continue ;	
		}
		has_quote = 1;
		if (in_quote == 0)
			in_quote = (*line)[i];
		else if (in_quote == (*line)[i])
			in_quote = 0;
		i++;
	}
	if (i > 0)
	{
		if (has_quote)
			tok -> type = WORD_Q; //word that contains quotes
		else
			tok -> type = WORD;
		tok -> str = (char *)malloc(i * sizeof(char) + 1);
		if (tok -> str == NULL)
			my_exit("Malloc error in parsing: get_next_tok\n", EXIT_FAILURE);
		ft_memcpy(tok -> str, *line, i);
		tok -> str[i] = '\0';
		tok -> len = i;
		(*line) += i;
		//printf("%s\n", tok -> str);
	}
	else 
	{
		
		tok -> type = OP;
		tok -> str = (char *)malloc(2 * sizeof(char) + 1);
		if (tok -> str == NULL)
			my_exit("malloc err pars tok", EXIT_FAILURE);
		tok -> str[1] = '\0';
		tok -> str[2] = '\0';
		tok -> str[0] = (*line)[i];
		if ((*line)[i + 1] == (*line)[i] && (*line)[i] != '|')
		{
			tok -> str[1] = (*line)[i];
			tok -> len = 2;
			(*line) += 2;
		}	
		else
		{
			tok -> len = 1;
			(*line) += 1;
		}
	}
	return (tok);
}
