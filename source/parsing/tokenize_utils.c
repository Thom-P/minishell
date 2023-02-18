/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 10:20:36 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/18 15:59:34 by tplanes          ###   ########.fr       */
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
