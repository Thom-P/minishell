/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:51:30 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/13 16:14:46 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "jmsh.h"

enum e_tok{WORD, WORD_Q, OP};

// Token 
typedef struct s_tok
{
	enum 	e_tok	type; // one of the enum
	char	*str;
	int		len;
}	t_tok;

// Main functions
int tokenize(char *line, t_list **tokens);

//Utils
int odd_num_quote(char *line);
int is_space(char c);
int is_only_space(char *line);
int ind_in_set(char c, char *set);

#endif
