/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:16:45 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/04 21:22:44 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

void	register_signals(void)
{
	int				fd;				
//	int				fd2;				
//	int				fd0;				
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
		//termios_p.c_lflag = termios_p.c_lflag & (~ECHOCTL);
		//termios_p.c_lflag &= (~ECHOCTL);
		//int j = tcsetattr(fd, TCSANOW, &termios_p);
		//printf("j=%i\n", j);
		if (termios_p.c_lflag & ECHOCTL)
			printf("aft: echo ctl active\n");
		else
			printf("aft: echo ctl inactive\n");

	}
	/*
	if (!isatty(fd2))
		printf("Not a tty\n");
	else
	{
		int i = tcgetattr(fd2, &termios_p);
		printf("i=%i\n", i);
		if (termios_p.c_lflag & ECHOCTL)
			printf("bef: echo ctl active\n");
		else
			printf("bef: echo ctl inactive\n");
		termios_p.c_lflag = termios_p.c_lflag & ~ECHOCTL;
		int j = tcsetattr(fd2, TCSANOW, &termios_p);
		printf("j=%i\n", j);
		if (termios_p.c_lflag & ECHOCTL)
			printf("aft: echo ctl active\n");
		else
			printf("aft: echo ctl inactive\n");

	}

	if (!isatty(fd0))
		printf("Not a tty\n");
	else
	{
		int i = tcgetattr(fd0, &termios_p);
		printf("i=%i\n", i);
		if (termios_p.c_lflag & ECHOCTL)
			printf("bef: echo ctl active\n");
		else
			printf("bef: echo ctl inactive\n");
		termios_p.c_lflag = termios_p.c_lflag & ~ECHOCTL;
		int j = tcsetattr(fd0, TCSANOW, &termios_p);
		printf("j=%i\n", j);
		if (termios_p.c_lflag & ECHOCTL)
			printf("aft: echo ctl active\n");
		else
			printf("aft: echo ctl inactive\n");

	}
*/

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	sigint_handler(int signum)
{
	(void) signum;
	printf("Caught a sigint!\n");
	g_status = 1;
	//rl_replace_line("test", 0);

	return ;
}
