/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:16:45 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/05 11:40:00 by tplanes          ###   ########.fr       */
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
	int				fd;				
	struct termios	termios_p;

	fd = STDOUT_FILENO;
	//fd2 = STDERR_FILENO;
	//fd0 = STDIN_FILENO;
	if (!isatty(fd))
		printf("Not a tty\n");
	else
	{
		int i = tcgetattr(fd, &termios_p);
		printf("i=%i\n", i);
		if (termios_p.c_lflag & ECHOCTL)
			printf("bef: echo ctl active\n");
		else
			printf("bef: echo ctl inactive\n");
		//termios_p.c_lflag &= ~ECHOCTL;
		int j = tcsetattr(fd, TCSANOW, &termios_p);
		printf("j=%i\n", j);
		if (termios_p.c_lflag & ECHOCTL)
			printf("aft: echo ctl active\n");
		else
			printf("aft: echo ctl inactive\n");

	}
*/