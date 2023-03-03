/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:20 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/03 18:15:07 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static char	*_get_prompt(int g_status);

static void	_fill_builtin_struc(t_builtin *builtin);

static void	_read_and_exec(char ***ptr_my_envp, t_builtin *builtin);

int	main(int ac, char **av, char **envp)
{
	//char	*line;
	//char	*prompt;
	//t_list	*exec_block;
	char	**my_envp;
	t_builtin	builtin;

	(void) ac;
	(void) av;
	g_status = 0;
	my_envp = copy_envp(envp);
	incr_shell_lvl(my_envp);
	_fill_builtin_struc(&builtin);
	//exec_block = NULL;
	print_jmsh_logo();
	while (1)
	{
		_read_and_exec(&my_envp, &builtin);
		
		/*prompt = _get_prompt(g_status);
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
		exec_line(exec_block, &my_envp, &builtin);
		ft_lstclear(&exec_block, &free_block);*/
	}
	return (0);
}

static void	_read_and_exec(char ***ptr_my_envp, t_builtin *builtin)
{
	char	*line;
	char	*prompt;
	t_list	*exec_block;

	exec_block = NULL;
	line = NULL;
	prompt = _get_prompt(g_status);
	line = readline(prompt);
	free(prompt);
	if (line == NULL)
		my_exit("Readline error\n", EXIT_FAILURE);
	if (*line == '\0')
	{
		free(line);
		return ;
	}
	add_history(line);
	if (parse_line(line, &exec_block, *ptr_my_envp) == -1)
	{
		g_status = 258;
		free(line);
		return ;		
	}
	free(line);
	exec_line(exec_block, ptr_my_envp, builtin);
	ft_lstclear(&exec_block, &free_block);
	return ;
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

// Construct builtin list and associated function pointer array
static void	_fill_builtin_struc(t_builtin *builtin)
{
	builtin -> names[0] = "echo";
	builtin -> names[1] = "cd";
	builtin -> names[2] = "pwd";
	builtin -> names[3] = "export";
	builtin -> names[4] = "unset";
	builtin -> names[5] = "env";
	builtin -> names[6] = "exit";
	builtin -> f_ptr[0] = b_echo;
	builtin -> f_ptr[1] = b_cd;
	builtin -> f_ptr[2] = b_pwd;
	builtin -> f_ptr[3] = b_export;
	builtin -> f_ptr[4] = b_unset;
	builtin -> f_ptr[5] = b_env;
	builtin -> f_ptr[6] = b_exit;
	return ;
}
