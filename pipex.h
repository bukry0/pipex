/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcili <bcili@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:31:20 by bcili             #+#    #+#             */
/*   Updated: 2025/03/13 17:31:20 by bcili            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char *s, unsigned int start, size_t len);

void	execute_child_process(char **argv, char **envp, int *fd);
void	execute_parent_process(char **argv, char **envp, int *fd);
char	*get_path_variable(char **envp);
void	ft_free(char **str);
char	*find_executable_path(char *cmd, char **envp);
void	error(char *message);
void	execute_command(char **envp, char *argv);


#endif