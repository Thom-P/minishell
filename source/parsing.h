/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:51:30 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/11 17:57:41 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "jmsh.h"

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


#endif
