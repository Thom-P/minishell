/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:16:45 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/06 18:32:40 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

void	set_parent_sigs(void)
{
	int				fd;				
	struct termios	termios_p;

	fd = STDOUT_FILENO;
	if (isatty(fd))
	{
		tcgetattr(fd, &termios_p);
		termios_p.c_lflag &= ~ECHOCTL;
		tcsetattr(fd, TCSANOW, &termios_p);
	}
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	sigint_parent(int signum)
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
	printf("heree\n");
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, sigint_child);
	return ;
}

void	sigint_child(int signum)
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
