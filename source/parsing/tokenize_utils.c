/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 10:20:36 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/22 13:31:19 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	new_token(t_list **tokens, t_tok **tok)
{
	t_list	*token;

	*tok = (t_tok *)malloc(sizeof(t_tok));
	if (*tok == NULL)
		my_exit("Malloc error in parsing: new_token\n", EXIT_FAILURE);
	token = ft_lstnew((void *)(*tok));
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

int	is_last_tok_null_wd(t_list **tokens)
{
	t_list	*last_token;
	t_tok	*last_tok;

	last_token = ft_lstlast(*tokens);
	if (last_token == NULL)
		return (0);
	last_tok = (t_tok *)(last_token -> content);
	if (last_tok -> type != word || last_tok -> str != NULL)
		return (0);
	return (1);
}

int	get_num_redir(t_list *token)
{
	int		num;
	t_tok	*tok;

	num = 0;
	while (token)
	{
		tok = (t_tok *)token -> content;
		if (tok -> type == op && *(tok -> str) == '|')
			break;
		else if (tok -> type == op)
			num += 1;
		token = token -> next;
	}
	return (num);
}

int	get_num_arg(t_list *token)
{
	int		num;
	t_tok	*tok;

	num = 0;
	while (token)
	{
		tok = (t_tok *)token -> content;
		if (tok -> type == op && *(tok -> str) == '|')
			break;
		else if (tok -> type == op)
		{
			token = token -> next;
			if (token)
				token = token -> next;
			continue ;
		}	
		else
			num += 1;
		token = token -> next;
	}
	return (num);
}
