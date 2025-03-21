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

void print_error(int error_code)
{
    if (error_code == 1)
        perror("Usage: infile cmd1 cmd2 outfile");
    else if (error_code == 2)
        perror("Pipe error");
    else if (error_code == 3)
        perror("Fork failed");
    else if (error_code == 4)
        perror("Error opening input file");
    else if (error_code == 5)
        perror("Error opening output file");
    else if (error_code == 6)
        perror("empty command");
    else if (error_code == 6)
        perror("command not found");
    exit(1);
}
void free_arg(char **argv)
{
    int i;
    i = -1;
    while (argv[++i])
        free(argv[i]);
    free(argv);
}

void setup_redirections(int argc, char **argv, int mode)
{
    int fd;

    if (mode == 0 || mode == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd < 0)
            print_error(4);
        dup2(fd, 0);
    }
    else if (mode == 1 || mode == 2)
    {
        fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd < 0)
            print_error(5);
        dup2(fd, 1);
    }
    close(fd);
}
