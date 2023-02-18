/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:51:30 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/18 16:01:05 by tplanes          ###   ########.fr       */
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

//Tokenize
void	new_token(t_list **tokens, t_tok** tok);
void	free_token(void *tok);
void    add_var_token(t_list **tokens, char **line);
void	add_dbl_quote_tokens(t_list **tokens, char **line);
void	build_word_tok(t_tok *tok, char **line, int i);
void	build_var_tok(t_tok *tok, char **line, int i);

//Parsing utils
int		odd_num_quote(char *line);
int		is_space(char c);
int		is_only_space(char *line);
int		ind_in_set(char c, char *set);

#endif
