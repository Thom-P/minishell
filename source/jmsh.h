/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:46 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/02 10:36:46 by tplanes          ###   ########.fr       */
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

//glob var
int	g_status;

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
void	exec_line(t_list *exec_blocks, char ***ptr_my_envp);

// Builtins
int		b_env(int ac, char **av, char **my_envp);
int		b_export(int ac, char **av, char ***ptr_my_envp);
int		b_unset(int ac, char **av, char ***ptr_my_envp);
int		b_exit(int ac, char **av); //envp to mod

// Builtin utils
int		get_env_size(char **my_envp);
int		is_var_name_legal(char *name);

// Utils
void	free_wd_array(char **arr);
void    free_block(void *tmp_block);
char	**copy_envp(char **envp);
void	incr_shell_lvl(char **my_envp);
int		ind_in_set(char c, char *set);
void	print_jmsh_logo(void);
void	my_exit(char *msg, int status);

// For debug
void	_print_block(void *block_tmp);

#endif
