/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:48:24 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/10 16:58:17 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jmsh.h"

int _odd_num_quote(char *line);

int _tokenize(char *line, t_list **tokens);

t_tok *_get_next_tok(char **line);

int _is_space(char c);

int _is_only_space(char *line);

int _ind_in_set(char c, char *set);

void _print_token(void *tok);

int	_is_space(char c);

int parse_line(char *line)
{
	t_list	*tokens;
	tokens = NULL;
	printf("Parsing: %s\n", line);
		
	if (_is_only_space(line))
	{
		printf("Error: only spaces...\n"); // to remove
		return (-1);
	}
	if (_odd_num_quote(line))
	{	
		printf("Error: missing quote\n");
		return (-1);
	}
	_tokenize(line, &tokens);
	ft_lstiter(tokens, _print_token);

	return (0);
}

int _tokenize(char *line, t_list **tokens)
{
	int	ini; //pointer to first char of curr word
	//int	end; //point to char right after curr word
	t_list	*token;

 	ini = 0;
	while (*line)
	{
		while (_is_space(*line))
			line++;
		if (*line != 0)
		{	
			token = ft_lstnew((void *)_get_next_tok(&line));
			if (token == NULL)
				my_exit("Error in parsing: lst_new\n", EXIT_FAILURE);
			ft_lstadd_back(tokens, token);
		}
	}
	return (1);
}

t_tok *_get_next_tok(char **line)
{
	int		i;
	char	*set = " <>|\"'";
	t_tok	*tok;

	tok = (t_tok *)malloc(sizeof(tok));
	if (tok == NULL)
		my_exit("Malloc error in parsing: get_next_tok\n", EXIT_FAILURE);
	i = 0;
	while ((*line)[i] && _ind_in_set((*line)[i],  set) == -1) //while not special char
		i++;
	if (i > 0)
	{
		tok -> type = WD;
		tok -> str = (char *)malloc(i * sizeof(char) + 1);
		if (tok -> str == NULL)
			my_exit("Malloc error in parsing: get_next_tok\n", EXIT_FAILURE);
		ft_memcpy(tok -> str, *line, i);
		tok -> str[i] = '\0';
		(*line += i);
		//printf("%s\n", tok -> str);
	}
	else 
	{
		tok -> type = OP;
		//tok -> str = NULL;
		tok -> str = malloc(1 * sizeof(char) + 1);
		if (tok -> str == NULL)
			my_exit("malloc err pars tok", EXIT_FAILURE);
		tok -> str[0] = set[_ind_in_set((*line)[i], set)];
		(*line += 1);
	}
	return (tok);
}

int _ind_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while(set[i])
	{
		if (c == set[i])
			return (i);
		i++;
	}
	return (-1);
}

int _is_only_space(char *line)
{
	while (*line)
	{	
		if (!_is_space(*line))
			return (0);
		line++;
	}
	return (1);
}

int _is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int _odd_num_quote(char *line)
{
	char	in_quote;

	in_quote = 0;
	while (*line)
	{
		if (*line != '"' && *line != '\'')
		{	
			line++;
			continue ;
		}
		if (in_quote == 0)
			in_quote = *line;
		else if (in_quote == *line)
			in_quote = 0;
		line++;	
	}
	if (in_quote)
		return (1);	
	return (0);
}

void _print_token(void *tok)
{
	printf("Token type: %i\n", ((t_tok *)tok)-> type);
	printf("Token val: %s\n", ((t_tok *)tok)-> str);
	return ;
}
