/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:51:29 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/04 17:04:47 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_tok_expand(t_tok *tok, char **my_envp);

void	expand_variables(t_list *tokens, char **my_envp)
{
	t_tok	*tok;

	while (tokens)
	{
		tok = (t_tok *)(tokens -> content);
		if (tok -> type == var)
			_tok_expand(tok, my_envp);
		tokens = tokens -> next;
	}	
}

static void	_tok_expand(t_tok *tok, char **my_envp)
{
	char	*value;

	value = get_var_from_envp(tok -> str, tok -> len, my_envp);
	if (value == NULL && tok -> len == 1 && *(tok -> str) == '?')
	{	
		value = ft_itoa(g_status);
		if (value == NULL)
			my_exit("ft_itoa error in _tok_expand\n", EXIT_FAILURE);
	}
	else if (value == NULL)
	{	
		value = (char *)malloc(1);
		if (value == NULL)
			my_exit("malloc error in _tok_expand\n", EXIT_FAILURE);
		*value = '\0';
	}
	free(tok -> str);
	tok -> str = value;
	tok -> len = ft_strlen(value);
	tok -> type = word;
	return ;
}

char	*get_var_from_envp(char *var_name, int var_len, char **my_envp)
{
	char	*value;

	value = NULL;
	while (*my_envp)
	{
		if (ft_strncmp(var_name, *my_envp, var_len) == 0
			&& (*my_envp)[var_len] == '=')
		{	
			value = ft_strdup((*my_envp) + var_len + 1);
			if (value == NULL)
				my_exit("Malloc error in var exp, ft_strdup\n", EXIT_FAILURE);
			break ;
		}
		my_envp++;
	}
	return (value);
}
