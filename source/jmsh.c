/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:20 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/24 15:50:32 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static void _print_splash_screen();

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	*prompt;
	t_list	*exec_block;

	(void) ac;
	(void) av;
	exec_block = NULL;
	prompt = "jmsh-1.0$ ";
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
		if (ft_strncmp(line, "exit", 5) == 0) //temporary hack to avoid writing builtin exit
		{
			free(line);
			return (0); //need to return status of last cmd instead
		}
		add_history(line);
		if (parse_line(line, &exec_block, envp) == -1) //will need to copy envp!
		{
			free(line);
			continue ;		
		}
		free(line);
		exec_line(exec_block, envp);
		ft_lstclear(&exec_block, &free_block);
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
