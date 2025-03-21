/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcili <bcili@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:26:48 by bcili             #+#    #+#             */
/*   Updated: 2025/03/13 17:26:48 by bcili            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child_process(char **argv, char **envp, int *fd)
{
	int	input_fd;

	input_fd = open(argv[1], O_RDONLY, 0777);
	if (input_fd == -1)
		error("Error opening input file");
	dup2(fd[1], 1);
	dup2(input_fd, 0);
	close(fd[0]);
	execute_command(envp, argv[2]);
}

void	execute_parent_process(char **argv, char **envp, int *fd)
{
	int	output_fd;

	output_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (output_fd == -1)
		error("Error opening output file");
	dup2(fd[0], 0);
	dup2(output_fd, 1);
	close(fd[1]);
	execute_command(envp, argv[3]);
}

void	execute_command(char **envp, char *argv)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = find_executable_path(cmd[0], envp);
	if (!path)
	{
		ft_free(cmd);
		error("Command not found");
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free(cmd);
		exit(126); //ERR_PRC
	}
	free(path);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (envp == NULL)
		error("Environment variables not found");
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error("Error creating pipe");
		pid1 = fork();
		if (pid1 == -1)
			error("Error creating process");
		if (pid1 == 0)
			execute_child_process(argv, envp, fd);
		execute_parent_process(argv, envp, fd);
	}
	else
		error("Incorrect number of arguments");
	return (0);
}
