/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 10:20:36 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/18 12:27:21 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	new_token(t_list **tokens, t_tok** tok)
{
	t_list	*token;

	*tok = (t_tok *)malloc(sizeof(t_tok));
	if (*tok == NULL)
		my_exit("Malloc error in parsing: new_token\n", EXIT_FAILURE);
	token = ft_lstnew((void *) (*tok));
	if (token == NULL)
		my_exit("Malloc rrror in parsing: lst_new\n", EXIT_FAILURE);
	ft_lstadd_back(tokens, token);
	return ;
}

void	free_token(void *tok)
{
	free(((t_tok *)tok)->str);
	free((t_tok *)tok);
	return ;
}

void	build_word_tok(t_tok *tok, char **line, int i)
{
    tok -> type = word;
    tok -> str = (char *)malloc(i * sizeof(char) + 1);
    if (tok -> str == NULL)
        my_exit("Malloc error in parsing: build_word_token\n", EXIT_FAILURE);
    ft_memcpy(tok -> str, *line, i);
    tok -> str[i] = '\0';
    tok -> len = i;
    (*line) += i;
    return ;
}

void	build_var_tok(t_tok *tok, char **line, int i)
{
    (*line) += 1;
	tok -> type = var;
    tok -> str = (char *)malloc(i * sizeof(char) + 1);
    if (tok -> str == NULL)
        my_exit("Malloc error in parsing: build_var_token\n", EXIT_FAILURE);
    ft_memcpy(tok -> str, *line, i);
    tok -> str[i] = '\0';
    tok -> len = i;
    (*line) += i;
    return ;
}
