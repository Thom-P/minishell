/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:20 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/01 13:19:31 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static int	g_status;

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	*prompt;
	t_list	*exec_block;
	char	**my_envp;

	(void) ac;
	(void) av;
	my_envp = copy_envp(envp);
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
		/*if (ft_strncmp(line, "exit", 5) == 0) //temporary hack to avoid writing builtin exit
		{
			free_wd_array(my_envp);
			free(line);
			return (0); //need to return status of last cmd instead
		}*/
		add_history(line);
		if (parse_line(line, &exec_block, my_envp) == -1) //will need to copy envp!
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
