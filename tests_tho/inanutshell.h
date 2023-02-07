/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inanutshell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:58:42 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/07 16:02:41 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INANUTSHELL_H
# define INANUTSHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

// Parsing
int parse_line(char *line);

#endif
