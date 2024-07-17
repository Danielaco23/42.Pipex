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

	if (argc < 5)
		return (ft_putstr_fd(ARGS_ERR_1, 2), ft_putstr_fd(ARGS_ERR_2, 2), 1);
	fds = ft_calloc((argc - 3) * 2, sizeof(int));
	if (init_fds((argc - 3), argv, fds))
		return (free(fds), ft_putstr_fd("Error opening fds", 2), 1);
	forker(fds, argv, env, (argc - 3));
	return (0);
}
