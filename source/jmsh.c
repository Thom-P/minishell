/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:20 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/03 16:59:45 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static char	*_get_prompt(int g_status);

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
	incr_shell_lvl(my_envp);
	exec_block = NULL;
	print_jmsh_logo();
	while (1)
	{
		prompt = _get_prompt(g_status);
		line = readline(prompt);
		free(prompt);
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
			g_status = 258;
			free(line);
			continue ;		
		}
		free(line);
		exec_line(exec_block, &my_envp);
		ft_lstclear(&exec_block, &free_block);
	}
	return (0);
}

static char	*_get_prompt(int g_status)
{
	char	*status;
	char	*prompt;
	char	*tmp;

	status = ft_itoa(g_status);
	if (status == NULL)
		my_exit("itoa error in jmsh.c\n", EXIT_FAILURE);
	if (g_status == 0)
		prompt = ft_strdup("\033[1;32mjmsh-1.0\033[0m $ ");
	else
	{	
		tmp = ft_strjoin("\033[1;31m{", status);
		if (tmp == NULL)
			my_exit("strjoin error in jmsh.c\n", EXIT_FAILURE);
		//printf("\033[1;31m");
		prompt = ft_strjoin(tmp, "}jmsh-1.0\033[0m $ ");
		free(tmp);
		//prompt = ft_strjoin(status, "@jmsh-1.0$\033[0m ");
	}
	if (prompt == NULL)
		my_exit("strjoin error in jmsh.c\n", EXIT_FAILURE);
	free(status);
	return (prompt);
}


