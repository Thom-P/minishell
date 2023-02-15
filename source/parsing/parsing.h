/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:51:30 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/15 15:15:44 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "jmsh.h"

//WORDQ is a word that contains one or several single quoted subparts (but no ")
//WORDQQ is a word that contains one or more double quoted parts (and 0 or more ')
enum e_tok{word, wordq, wordqq, op};

// Token 
typedef struct s_tok
{
	enum e_tok	type;
	char		*str;
	int			len;
}	t_tok;

// Main functions
int		tokenize(char *line, t_list **tokens);

//Utils
int		odd_num_quote(char *line);
int		is_space(char c);
int		is_only_space(char *line);
int		ind_in_set(char c, char *set);
int		verify_tokens(t_list **tokens);
void	free_token(void *tok);

#endif
