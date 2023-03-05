/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:52:14 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/05 18:25:17 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "jmsh.h"

// Structures if any

typedef struct s_exec
{
	int		nb_pipes;
	int		nb_cmd;
	int		*pipe;
	int		**fd;
	int		fd_in;
	int		fd_out;
	int		nb_blocks;
	int		n;
	char	**path;
	pid_t	*pid;
}	t_exec;

// Main functions (except exec_line(), already defined in jmsh.h)

// Exec utils
// static int	get_index_builtin(char *cmd, char *names[N_BUILTIN]);
int			launch_exec(t_list *exec_blocks, t_builtin *builtin,
				char ***my_env);
void		fork_init(t_exec *exec, t_block *blocks, t_builtin *builtin,
				char **my_env);
void		child(t_exec *exec, t_block *blocks, t_builtin *builtin,
				char **my_env);
char		*find_cmd(t_exec *exec, char *cmd);
char		*access_cmd(t_exec *exec, char *cmd);
void		pipe_init(t_exec *exec, int **fd);
void		close_pipe(t_exec *exec);

#endif
