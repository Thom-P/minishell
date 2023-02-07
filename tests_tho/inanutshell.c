/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inanutshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:54:17 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/07 14:47:35 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inanutshell.h"

void parse_line(char *line);

int main(int ac, char **av, char **envp)
{
	char	*line;
	char	*prompt;

	(void) ac;
	(void) av;
	(void) envp;
	prompt = "InaNutSHELL % ";
	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
		{	
			free(line);
			exit(EXIT_FAILURE);
		}
		if (*line)
		{
			add_history(line);
			parse_line(line);
			//exec_line();
		}
		free(line);
	}
	return (0);
}

void parse_line(char *line)
{
	printf("Parsing: %s\n", line);
	return ;
}
