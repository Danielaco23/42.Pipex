/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:10:11 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/05/21 12:10:13 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./Libft/libft.h"
# include <stdio.h>
# include <wait.h>

# define ARGS_ERR_1 "Error: wrong number of arguments.\nStructure must be:\n"
# define ARGS_ERR_2 "./pipex infile command1 command2 outfile\n"

typedef struct s_index
{
	int		index;
	int		total;
}	t_index;

void	arr_freer(char **arr);
int		forker(int *fds, char **argv, char **env, int n_com);
void	execution(int *fds, char *argv, char **env, t_index index);
void	fd_arr_closer(int *fds, int last);

#endif
