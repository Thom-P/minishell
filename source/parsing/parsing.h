/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:51:30 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/26 17:25:06 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "jmsh.h"

enum e_tok{word, space, op, var};

// Token 
typedef struct s_tok
{
	enum e_tok	type;
	char		*str;
	int			len;
}	t_tok;

// Main functions
int		tokenize(char *line, t_list **tokens);
int		verify_tokens(t_list **tokens);
void	process_heredocs(t_list *tokens);
void	build_exec_blocks(t_list *tokens, t_list **exec_blocks);

//Tokenize
void	new_token(t_list **tokens, t_tok **tok);
void	free_token(void *tok);
void	add_var_token(t_list **tokens, char **line);
void	add_dbl_quote_tokens(t_list **tokens, char **line);
void	build_word_tok(t_tok *tok, char **line, int i);
void	build_var_tok(t_tok *tok, char **line, int i);
int		is_last_tok_null_wd(t_list **tokens);

//Variable expansion
void	expand_variables(t_list *tokens, char **my_envp);
char	*get_var_from_envp(char *var_name, int var_len, char **my_envp);

//Merge words and remove space tokens
void	merge_word_toks(t_list *tokens);
void	remove_space_toks(t_list **tokens);

//Build exec blocks
int		get_num_arg(t_list *token);
int		get_num_redir(t_list *token);
void	new_exec_block(t_list **ex_bks, t_block **bk, int n_redir, int n_arg);

//Parsing utils
int		odd_num_quote(char *line);
int		is_space(char c);
int		is_only_space(char *line);
int		ind_in_set(char c, char *set);

#endif
