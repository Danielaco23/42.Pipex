/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:33:08 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/05/22 11:38:00 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	arr_freer(char **arr)
{
	int		i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i ++;
		}
		free(arr);
	}
}

void	fd_arr_closer(int *fds, int size)
{
	while (size >= 0)
	{
		close(fds[size]);
		size --;
	}
}

int	forker(int *fds, char **argv, char **env, int n_com)
{
	t_index	index;
	int		pid;

	index.index = 0;
	index.total = n_com -1;
	while (index.index < n_com)
	{
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			execution(fds, argv[index.index +2], env, index);
		index.index ++;
	}
	fd_arr_closer(fds, (n_com * 2) - 1);
	wait(NULL);
	wait(NULL);
	return (0);
}
