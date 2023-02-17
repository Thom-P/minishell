/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:28:54 by tplanes           #+#    #+#             */
/*   Updated: 2023/02/17 15:38:54 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	num_sgl_quote_pairs(char *str)
{
	int		num;
	int		flag_in_quote;

	num = 0;
	flag_in_quote = -1;
	while (*str)
	{
		if (*str++ != '\'')
			continue ;
		flag_in_quote *= -1;
		if (flag_in_quote == 1)
			num += 1;
	}
	return (num);
}
