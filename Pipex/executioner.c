/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:33:18 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/05/22 11:37:39 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**path_array_b(char **env)
{
	int		i;
	char	*path;
	char	**path_split;

	i = 0;
	while (env[i] != NULL)
	{
		path = ft_strnstr(env[i], "PATH=/h", ft_strlen(env[i]));
		if (path != NULL)
		{
			path_split = ft_split(path, ':');
			if (!path_split)
				exit(EXIT_FAILURE);
			path = path_split[0];
			path_split[0] = ft_strdup(&path[5]);
			free(path);
			return (path_split);
		}
		i++;
	}
	ft_putstr_fd("Command not found\n", 2);
	exit(EXIT_FAILURE);
}

static char	*where_is_comm_b(char *command, char **env)
{
	char	*path_program;
	char	**path_arr;
	int		i;

	if (access(command, X_OK) == 0)
		return (command);
	else
	{
		command = ft_strjoin("/", command);
		if (!command)
			exit(EXIT_FAILURE);
		path_arr = path_array_b(env);
		if (!path_arr)
			exit(EXIT_FAILURE);
		i = 0;
		while (path_arr[i] != NULL)
		{
			path_program = ft_strjoin(path_arr[i ++], command);
			if (access(path_program, X_OK) != -1)
				return (arr_freer(path_arr), free(command), path_program);
			free(path_program);
		}
		exit(EXIT_FAILURE);
	}
}

static int	first_pipe(int *fds, t_index index)
{
	if (index.index != 0 || fds[0] == -1)
		return (1);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		return (close(fds[0]), close(fds[1]), 1);
	close(fds[0]);
	close(fds[2]);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		return (close(fds[1]), 1);
	close(fds[1]);
	return (0);
}

static int	last_pipe(int *fds, t_index index)
{
	int		*pipe;

	if (index.index == 0)
		return (1);
	pipe = &fds[(index.index * 2) - 1];
	if (pipe[2] == -1)
		return (1);
	close(pipe[0]);
	if (dup2(pipe[1], STDIN_FILENO) == -1)
		return (1);
	close(pipe[1]);
	if (index.index < index.total)
		close(pipe[3]);
	if (dup2(pipe[2], STDOUT_FILENO) == -1)
		return (1);
	close(pipe[2]);
	return (0);
}

void	execution(int *fds, char *arg, char **env, t_index index)
{
	char	*path_program;
	char	*command;
	char	**arguments;

	arguments = ft_split(arg, ' ');
	if (!arguments)
		exit(EXIT_FAILURE);
	command = arguments[0];
	path_program = where_is_comm_b(command, env);
	if (first_pipe(fds, index) && last_pipe(fds, index))
		exit(EXIT_FAILURE);
	execve(path_program, arguments, env);
	free(path_program);
	arr_freer(arguments);
	exit(EXIT_FAILURE);
}
