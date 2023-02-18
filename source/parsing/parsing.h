/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:51:30 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/18 11:00:53 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "jmsh.h"

/*
WORDQ is a word that contains one or several 
single quoted subparts (but no ")
WORDQQ is a word that contains one or several
double quoted parts (and 0 or more ')
*/
enum e_tok{word, space, op, var, wordq, wordqq};

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
void	process_quotes(t_list **ptr_tokens);

//Tokenize utils
void	new_token(t_list **tokens, t_tok** tok);
void	free_token(void *tok);
void	build_word_tok(t_tok *tok, char **line, int i);

//Parsing utils
int		odd_num_quote(char *line);
int		is_space(char c);
int		is_only_space(char *line);
int		ind_in_set(char c, char *set);

//Process quotes utils
int		num_sgl_quote_pairs(char *str);

#endif
