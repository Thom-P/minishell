/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:46 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/24 16:01:08 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JMSH_H
# define JMSH_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>

# include "libft.h"
# include "get_next_line.h"

// here doc already converted to <(tmp_file) in parsing
enum e_redir{in = 1, out = 2, append = 3}; 

//n_arg include command
typedef struct s_block
{
	int				n_redir;
	int				n_arg;
	enum e_redir	*redir;
	char			**files;
	char			**cmd_args;	
}	t_block;

// Parsing
int		parse_line(char *line, t_list **exec_block, char **my_envp);

// Execution
void	exec_line(t_list *exec_blocks, char **envp);

// Utils
void	my_exit(char *msg, int status);
void	free_wd_array(char **arr);
void    free_block(void *tmp_block);

// For debug
void	_print_block(void *block_tmp);

#endif
