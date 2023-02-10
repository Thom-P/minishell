/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:20 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/10 17:34:51 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static void _print_splash_screen();

int main(int ac, char **av, char **envp)
{
	char	*line;
	char	*prompt;

	(void) ac;
	(void) av;
	(void) envp;
	prompt = "jmsh % ";
	_print_splash_screen();
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

static void _print_splash_screen()
{
	int		fd;
	char	*line;

	fd = open("ascii.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
	return ;
}
