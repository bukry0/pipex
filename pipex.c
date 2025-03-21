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


char	*get_path_variable(char **envp)
{
    int		i;
	char	*path_env;
    
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
        path_env = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	return (path_env);
}

void	ft_free(char **str)
{
	int	i;
    
	i = 0;
	while (str[i] != 0)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*find_executable_path(char *cmd, char **envp)
{
    int		i;
	char	**path;
	char	*dir_with_slash;
	char	*full_cmd_path;
	char	*path_env;
    
	path_env = get_path_variable(envp);
	path = ft_split(path_env, ':');
	free(path_env);
	i = -1;
	while (path[++i])
	{
        dir_with_slash = ft_strjoin(path[i], "/");
		full_cmd_path = ft_strjoin(dir_with_slash, cmd);
		free(dir_with_slash);
		if (access(full_cmd_path, F_OK) == 0)
		{
			ft_free(path);
			return (full_cmd_path);
		}
		free(full_cmd_path);
	}
	ft_free(path);
	return (NULL);
}

void	error(char *message)
{
	perror(message);
	exit(1);
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
		exit(126); // ERR_PRC -> Komut çalıştırılamadığında
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
