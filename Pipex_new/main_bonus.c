/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:13:06 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/07/17 12:13:07 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	init_fds(int n_com, char **argv, int *fds)
{
	int		tmp;
	int		i;

	tmp = open(argv[1], __O_DIRECTORY);
	if (tmp != -1)
		return (close(tmp), close(fds[0]), 1);
	fds[0] = open(argv[1], O_RDONLY);
	if (fds[0] < 0)
		return (1);
	i = 0;
	while (i < n_com - 1)
	{
		if (pipe(&fds[(i * 2) + 1]))
			return (fd_arr_closer(fds, (i * 2) + 2), 1);
		tmp = fds[(i * 2) + 2];
		fds[(i * 2) + 2] = fds[(i * 2) + 1];
		fds[(i++ *2) + 1] = tmp;
	}
	fds[(i * 2) + 1] = open(argv[n_com + 2], 0100 | 01 | 01000, 0755);
	tmp = open(argv[n_com + 2], __O_DIRECTORY);
	if (tmp != -1)
		return (fd_arr_closer(fds, (n_com * 2) - 1), close(tmp), 1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		*fds;
	t_index	index;

	if (argc < 5)
		return (ft_putstr_fd(ARGS_ERR_1, 2), ft_putstr_fd(ARGS_ERR_2, 2), 1);
	index.i = 0;
	index.n_com = argc - 3;
	index.total = index.n_com - 1;
	index.fd_count = index.n_com * 2;
	fds = ft_calloc(index.n_com * 2, sizeof(int));
	if (!fds)
		return (ft_putendl_fd("Malloc error.", 2), 1);
	if (init_fds(index.n_com, argv, fds))
		return (free(fds), ft_putendl_fd("Error opening fds", 2), 1);
	forker(fds, argv, env, &index);
	free(fds);
	return (0);
}
