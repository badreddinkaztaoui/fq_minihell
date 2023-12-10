/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmpfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 22:34:48 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/10 02:41:46 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int ft_tmpfile(char *str)
// {
// 	int fd;
// 	char *path;
// 	char *filename;

// 	path = "/tmp/tmpXXXXXX";
// 	filename = malloc(ft_strlen(path) + 1);
// 	if (!filename)
// 	{
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		free(filename);
// 		exit(EXIT_FAILURE);
// 	}
// 	unlink(filename);
// 	free(filename);
// 	return (fd);
// }