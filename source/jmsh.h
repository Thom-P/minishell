/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmsh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:20:46 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/11 17:58:32 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JMSH_H
# define JMSH_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# include "libft.h"
# include "get_next_line.h"

// Parsing
int parse_line(char *line);

// Execution


// Utils
void my_exit(char *msg, int status);


#endif