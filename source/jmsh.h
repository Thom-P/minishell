/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:46 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/21 16:11:33 by tplanes          ###   ########.fr       */
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

enum e_redir{in, out, append, here_doc};

typedef struct s_block
{
	enum e_redir	*redir;
	int				n_redir;
	char			**file_array;
	char			**cmd_args;	
}	t_block;


// Parsing
int parse_line(char *line, t_list **exec_block, char **my_envp);

// Execution


// Utils
void my_exit(char *msg, int status);


#endif
