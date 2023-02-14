/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:11:53 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/14 15:04:09 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ind_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (i);
		i++;
	}
	return (-1);
}

int	is_only_space(char *line)
{
	while (*line)
	{	
		if (!is_space(*line))
			return (0);
		line++;
	}
	return (1);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	odd_num_quote(char *line)
{
	char	in_quote;

	in_quote = 0;
	while (*line)
	{
		if (*line != '"' && *line != '\'')
		{
			line++;
			continue ;
		}
		if (in_quote == 0)
			in_quote = *line;
		else if (in_quote == *line)
			in_quote = 0;
		line++;
	}
	if (in_quote)
		return (1);
	return (0);
}

/* 
Return error if:
- first token is pipe
- last token is any operator
*/
int verify_tokens(t_list **tokens)
{
	t_tok 	*tok;

	tok = (t_tok *)(*tokens)-> content;
	if (tok -> type == op && tok -> str[0] == '|')
	{	
		printf("jmsh: syntax error near unexpected token `|'\n");
		ft_lstclear(tokens, &free_token);
		return (-1);
	}
    tok = ft_lstlast(*tokens)-> content;
	if (tok -> type == op)
	{	
		printf("jmsh: syntax error near unexpected token `newline'\n");
		ft_lstclear(tokens, &free_token);
		return (-1);
	}


	return (0);
}

void free_token(void *tok)
{
	free(((t_tok *)tok)->str);
	free((t_tok *)tok);
	return ;
}
