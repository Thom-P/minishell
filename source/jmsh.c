/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:20 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/05 11:52:32 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static char	*_get_prompt(int g_status);

static void	_fill_builtin_struc(t_builtin *built);

static void	_read_and_exec(char **line, char ***ptr_my_envp, t_builtin *built);

int	main(int ac, char **av, char **envp)
{
	t_builtin	built;
	char		**my_envp;
	char		*line;

	(void) ac;
	(void) av;
	set_parent_sigs();
	g_status = 0;
	my_envp = copy_envp(envp);
	incr_shell_lvl(my_envp);
	_fill_builtin_struc(&built);
	print_jmsh_logo();
	while (1)
	{
		_read_and_exec(&line, &my_envp, &built);
		free(line);
	}
	return (0);
}

static void	_read_and_exec(char **line, char ***ptr_my_envp, t_builtin *built)
{
	char	*prompt;
	t_list	*exec_block;
	int		parse_status;

	exec_block = NULL;
	prompt = _get_prompt(g_status);
	*line = readline(prompt);
	free(prompt);
	if (*line == NULL)
		my_exit("", g_status);
	if (**line == '\0')
		return ;
	add_history(*line);
	parse_status = parse_line(*line, &exec_block, *ptr_my_envp);
	if (parse_status < 0)
	{
		if (parse_status == -1)
			g_status = 258;
		return ;
	}
	free(*line);
	*line = NULL;
	exec_line(exec_block, ptr_my_envp, built);
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
		prompt = ft_strjoin(tmp, "}jmsh-1.0\033[0m $ ");
		free(tmp);
	}
	if (prompt == NULL)
		my_exit("strjoin error in jmsh.c\n", EXIT_FAILURE);
	free(status);
	return (prompt);
}

// Construct builtin list and associated function pointer array
static void	_fill_builtin_struc(t_builtin *built)
{
	built -> names[0] = "echo";
	built -> names[1] = "cd";
	built -> names[2] = "pwd";
	built -> names[3] = "export";
	built -> names[4] = "unset";
	built -> names[5] = "env";
	built -> names[6] = "exit";
	built -> f_ptr[0] = b_echo;
	built -> f_ptr[1] = b_cd;
	built -> f_ptr[2] = b_pwd;
	built -> f_ptr[3] = b_export;
	built -> f_ptr[4] = b_unset;
	built -> f_ptr[5] = b_env;
	built -> f_ptr[6] = b_exit;
	return ;
}
