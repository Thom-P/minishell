/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inanutshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:54:17 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/07 16:02:24 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inanutshell.h"

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
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (parse_line(line) == -1)
		{
			free(line);
			continue ;		
		}
		free(line);
		//exec_line();
	}
	return (0);
}
