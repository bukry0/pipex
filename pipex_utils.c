/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcili <bcili@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:32:10 by bcili             #+#    #+#             */
/*   Updated: 2025/03/13 17:32:10 by bcili            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	error(char *message)
{
	perror(message);
	exit(1);
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
