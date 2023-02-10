/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:46 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/10 13:23:14 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JMSH_H
# define JMSH_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"


// Parsing

# define WD 1 // regular word
# define SQ_WORD 2 // single quoted word
# define DQ_WORD 3 // double quoted word
# define SP 4 // space (to denote word separation or not when quoted subparts)
# define OP 5 // operator (redirs or pipe)

// Token 
typedef struct s_tok
{
	int		type; // one of the const defined above
	char	*str;
}	t_tok;

int parse_line(char *line);

#endif
