/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:16:45 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/06 20:40:21 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static void	sigint_prompt(int signum);

void	set_sigs(int is_parent, int is_child_running)
{
	int				fd;				
	struct termios	termios_p;

	if (is_parent && !is_child_running)
	{
		fd = STDOUT_FILENO;
		if (isatty(fd))
		{
			tcgetattr(fd, &termios_p);
			termios_p.c_lflag &= ~ECHOCTL;
			tcsetattr(fd, TCSANOW, &termios_p);
		}
		signal(SIGINT, sigint_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if(is_parent)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	return ;
}

static void	sigint_prompt(int signum)
{
	(void) signum;
	g_status = 1;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	return ;
}

/*
void	set_child_sigs(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

*void	sigint_child(int signum)
{
	//(void) signum;
	ft_printf(STDERR_FILENO, "child received sig %i\n", signum);
	g_status = 128 + signum;
	//rl_replace_line("", 0);
	//printf("\n");
	//rl_on_new_line();
	//rl_redisplay();
	my_exit("", g_status);
}
*/
