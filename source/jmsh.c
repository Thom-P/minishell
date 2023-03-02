/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:20 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/02 10:44:54 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	*prompt;
	t_list	*exec_block;
	char	**my_envp;

	(void) ac;
	(void) av;
	g_status = 0;
	my_envp = copy_envp(envp);
	//incr_shell_lvl(my_envp);
	exec_block = NULL;
	prompt = "jmsh-1.0$ ";
	print_jmsh_logo();
	printf("status=%i\n", g_status);
	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
			exit(EXIT_FAILURE);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (parse_line(line, &exec_block, my_envp) == -1)
		{
			free(line);
			continue ;		
		}
		free(line);
		exec_line(exec_block, &my_envp);
		ft_lstclear(&exec_block, &free_block);
	}
	return (0);
}
