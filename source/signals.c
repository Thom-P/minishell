/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:16:45 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/06 21:37:20 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

static void	_sigint_prompt(int signum);

static void	_switchof_echoctl(int fd);

static void	_switchon_echoctl(int fd);

void	set_sigs(int is_parent, int is_child_running)
{
	int				fd;				

	fd = STDOUT_FILENO;
	if (is_parent && !is_child_running)
	{
		_switchof_echoctl(fd);
		signal(SIGINT, _sigint_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (is_parent)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		_switchon_echoctl(fd);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	return ;
}

static void	_switchof_echoctl(int fd)
{
	struct termios	termios_p;

	if (isatty(fd))
	{
		tcgetattr(fd, &termios_p);
		termios_p.c_lflag &= ~ECHOCTL;
		tcsetattr(fd, TCSANOW, &termios_p);
	}
	return ;
}

static void	_switchon_echoctl(int fd)
{
	struct termios	termios_p;

	if (isatty(fd))
	{
		tcgetattr(fd, &termios_p);
		termios_p.c_lflag |= ECHOCTL;
		tcsetattr(fd, TCSANOW, &termios_p);
	}
	return ;
}

static void	_sigint_prompt(int signum)
{
	(void) signum;
	g_status = 1;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	return ;
}
