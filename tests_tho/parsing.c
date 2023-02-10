/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:48:24 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/10 13:55:14 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

int _odd_num_quote(char *line);

int _tokenize(char *line, t_list **tokens);

int _is_space(char c);

int _is_only_space(char *line);

int parse_line(char *line)
{
	t_list	**tokens;
	tokens = NULL;
	printf("Parsing: %s\n", line);
		
	if (_is_only_space(line))
	{
		printf("Error: only spaces...\n"); // to remove
		return (-1);
	}
	if (_odd_num_quote(line))
	{	
		printf("Error: missing quote\n");
		return (-1);
	}
	_tokenize(line, tokens);

	return (0);
}

int _tokenize(char *line, t_list **tokens)
{
	int	ini; //pointer to first char of curr word
	int	end; //point to char right after curr word
	
	t_tok tok;
   
	ini = 0;
	while (is_space(line))
		line++;
	
}

int _is_only_space(char *line)
{
	while (*line)
	{	
		if (!_is_space(*line))
			return (0);
		line++;
	}
	return (1);
}

int _is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int _odd_num_quote(char *line)
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
