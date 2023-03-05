/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:46 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/05 11:36:38 by tplanes          ###   ########.fr       */
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
# include <termios.h>

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define N_BUILTIN 7

// Readline fix
void	rl_replace_line(const char *text, int clear_undo);

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

// Builtin list and function pointer struct
typedef struct s_builtin
{
	char	*names[N_BUILTIN];
	int		(*f_ptr[N_BUILTIN])(int ac, char **av, char ***ptr_my_envp);
}	t_builtin;

// Parsing
int		parse_line(char *line, t_list **exec_block, char **my_envp);

// Execution
void	exec_line(t_list *exec_blocks, char ***ptr_my_envp, t_builtin *builtin);

// Builtins
int		b_echo(int ac, char **av, char ***ptr_my_envp);
int		b_cd(int ac, char **av, char ***ptr_my_envp);
int		b_pwd(int ac, char **av, char ***ptr_my_envp);
int		b_export(int ac, char **av, char ***ptr_my_envp);
int		b_unset(int ac, char **av, char ***ptr_my_envp);
int		b_env(int ac, char **av, char ***ptr_my_envp);
int		b_exit(int ac, char **av, char ***ptr_my_envp);

// Builtin utils
int		get_env_size(char **my_envp);
int		is_var_name_legal(char *name);

// Signals
void	set_parent_sigs(void);
void	sigint_parent(int signum);

// Utils
void	free_wd_array(char **arr);
void	free_block(void *tmp_block);
char	**copy_envp(char **envp);
void	incr_shell_lvl(char **my_envp);
int		ind_in_set(char c, char *set);
void	print_jmsh_logo(void);
void	my_exit(char *msg, int status);

// For debug
void	_print_block(void *block_tmp);

#endif
