/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:51:30 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/13 15:43:13 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "jmsh.h"

//# define WD 1 // regular word
//# define Q_WD 2 // word including quotes (1 or several pairs of "" or '')
//# define OP 3 // operator (redirs or pipe)

enum e_tok{WORD, WORD_Q, OP};

// Token 
typedef struct s_tok
{
	//int		type; // one of the const defined above
	enum 	e_tok	type; // one of the enum
	char	*str;
	int		len;
}	t_tok;


#endif
