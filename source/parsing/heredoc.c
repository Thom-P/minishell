/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:13:51 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/26 17:19:27 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_create_tmp_file(t_list *tokens, char *str_ind_doc);

static void	_copy_input_to_file(int fd, char *delim);

void	process_heredocs(t_list *token)
{
	t_tok	*tok;
	int		ind_doc;
	char	*str_ind_doc;

	ind_doc = 0;
	while (token)
	{
		tok = (t_tok *)(token -> content);
		if (tok -> type == op && tok -> str[0] == '<' && tok -> str[1] == '<')
		{
			tok -> str[1] = '\0';
			tok -> len = 1;
			token = token -> next;
			str_ind_doc = ft_itoa(ind_doc);
			if (str_ind_doc == NULL)
				my_exit("Malloc error in process_heredocs itoa\n", EXIT_FAILURE);
			_create_tmp_file(token, str_ind_doc);
			ind_doc++;
		}
		token = token -> next;
	}
	return ;
}

static void	_create_tmp_file(t_list *token, char *str_ind_doc)
{
	t_tok	*tok;
	char	*delim;
	char	*tmp_file;
	int		fd;

	tok = (t_tok *)(token -> content);
	delim = tok -> str;
	tmp_file = ft_strjoin(".tmp_hdoc_", str_ind_doc);
	free(str_ind_doc);
	if (tmp_file == NULL)
		my_exit("Malloc error in create tmp file ft_strjoin\n", EXIT_FAILURE);
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		my_exit("Error in creating tmp_file for heredoc\n", EXIT_FAILURE);
	_copy_input_to_file(fd, delim);
	close(fd);
	tok -> str = tmp_file;
	tok -> len = ft_strlen(tmp_file);
	free(delim);
	return ;
}

static void	_copy_input_to_file(int fd, char *delim)
{
	char	*line;

	line = readline(">");
	while (line && ft_strncmp(line, delim, ft_strlen(delim)) != 0)
	{
		write(fd, line, ft_strlen(line));
		free(line);
		write(fd, "\n", 1);
		line = readline(">");
	}
	free(line);
	return ;
}
