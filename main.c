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
	fds[0] = open(argv[1], O_RDONLY);
	if (pipe(&fds[1]))
		return (close(fds[0]), 1);
	fds[3] = fds[2];
	fds[2] = fds[1];
	fds[1] = fds[3];
	fds[3] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		fds[4];
	t_index	index;

	if (argc != 5)
		return (ft_putstr_fd(ARGS_ERR_1, 2), ft_putstr_fd(ARGS_ERR_2, 2), 1);
	init_fds(argv, fds);
	index.i = 0;
	index.n_com = argc - 3;
	index.total = index.n_com - 1;
	index.fd_count = index.n_com * 2;
	index.bonus = 0;
	index.in = argv[1];
	index.out = argv[argc -1];
	forker(fds, argv, env, &index);
	return (0);
}

// pipe(&pipe[0]) pipe: [fd1] [fd2] [] []

// Proceso 1: W -> fd1   dup2(fd1, STDOUT_FILENO) close(fd2) close(fd1)
// PADRE: close(fd1);
// Proceso 2: fd2 -> R   dup2(fd2, STDIN_FILENO) close(fd2) close(fd1)
// PADRE:close (fd2);
