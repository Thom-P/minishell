/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:47:32 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/01 17:21:22 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_line(t_list *exec_blocks, char ***ptr_my_envp)
{
	//temporary action: print the content of the exec blocks
	ft_lstiter(exec_blocks, &_print_block);
	printf("\n");
	
	//see the readme file

	//Temporary builtin test (Thomas)
	t_block	*block = exec_blocks -> content;
	int	ac = block -> n_arg;
	char **av = block -> cmd_args;
	//int	ind_builtin = _get_index_builtin(av[0]);
	//if (ind_builtin != -1)
	//	g_status = f_array[]
	if (ft_strncmp(av[0], "exit", 5) == 0)
		g_status = b_exit(ac, av);
	if (ft_strncmp(av[0], "env", 4) == 0)
		g_status = b_env(ac, av, *ptr_my_envp);
	if (ft_strncmp(av[0], "export", 7) == 0)
		g_status = b_export(ac, av, ptr_my_envp);
	if (ft_strncmp(av[0], "unset", 6) == 0)
		g_status = b_unset(ac, av, ptr_my_envp);

	return ;
}

/*
// returns index of bultin in list below or -1 if not a builtin
static int	_get_index_builtin(char *name)
{
	char	*b_array[8];
	int		ind;

	ind = 0;
	b_array[0] = "echo";
	b_array[1] = "cd";
	b_array[2] = "pwd";
	b_array[3] = "export";
	b_array[4] = "unset";
	b_array[5] = "env";
	b_array[6] = "exit";
	b_array[7] = NULL;
	while (b_array[ind])
	{
		if (ft_strncmp(name, b_array[ind], ft_strlen(name) + 1) == 0)
			return (ind);
		ind++;
	}
	return (-1);
}

static	int _exec_builtin(int ind_builtin, int ac, char **av, char)

static int  ft_print(va_list ap, t_tags *tags, int *nb_chr_prt)
{
    char    *spec_set;
    int     (*f_ptr[9])(va_list ap, t_tags *tags, int *nb_chr_prt);
    int     ind_spec;

	spec_set = "cdisuxXp%";
    f_ptr[0] = ft_print_str_char;
    f_ptr[1] = ft_print_int;
    f_ptr[2] = ft_print_int;
    f_ptr[3] = ft_print_str_char;
    f_ptr[4] = ft_print_int;
    f_ptr[5] = ft_print_hex;
    f_ptr[6] = ft_print_hex;
    f_ptr[7] = ft_print_hex;
    f_ptr[8] = ft_print_str_char;
    ind_spec = ft_ind_in_set(tags -> spec, spec_set);
    if (f_ptr[ind_spec](ap, tags, nb_chr_prt))
        return (-1);
    return (0);
}
*/

