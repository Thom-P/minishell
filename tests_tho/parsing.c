/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:48:24 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/07 16:15:11 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inanutshell.h"

int _odd_num_quote(char *line);

int parse_line(char *line)
{
	printf("Parsing: %s\n", line);
	
	if (_odd_num_quote(line))
	{	
		printf("Error: missing quote\n");
		return (-1);
	}

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
