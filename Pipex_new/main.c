/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:10:19 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/05/22 11:38:12 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	init_fds(char **argv, int *fds)
{
	fds[3] = open(argv[1], __O_DIRECTORY);
	if (fds[3] < 0)
	{
		fds[3] = open(argv[4], __O_DIRECTORY);
		if (fds[3] < 0)
		{
			fds[0] = open(argv[1], O_RDONLY);
			if (fds[0] < 0)
				return (1);
			if (pipe(&fds[1]))
				return (close(fds[0]), 1);
			fds[3] = fds[2];
			fds[2] = fds[1];
			fds[1] = fds[3];
			fds[3] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0755);
			if (fds[3] < 0)
				return (fd_arr_closer(fds, 2), 1);
		}
		else
			return (close(fds[3]));
	}
	else
		return (close(fds[3]), 1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		fds[4];
	t_index	index;

	if (argc != 5)
		return (ft_putstr_fd(ARGS_ERR_1, 2), ft_putstr_fd(ARGS_ERR_2, 2), 1);
	if (init_fds(argv, fds))
		return (ft_putstr_fd("Error opening fds", 2), 1);
	index.i = 0;
	index.n_com = argc - 3;
	index.total = index.n_com - 1;
	index.fd_count = index.n_com * 2;
	forker(fds, argv, env, &index);
	return (0);
}
