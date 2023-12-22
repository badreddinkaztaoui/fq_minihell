/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uheredoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:19:00 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/22 01:27:08 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_genname(void)
{
	char	*filename;
	int		fd;
	int		i;

	filename = malloc(R_FILE_SIZE + 1);
	fd = open(R_FILE, O_RDONLY);
	i = 0;
	while (i < R_FILE_SIZE)
	{
		read(fd, &filename[i], 1);
		while (!isalpha(filename[i]))
			read(fd, &filename[i], 1);
		i++;
	}
	close(fd);
	filename[R_FILE_SIZE] = '\0';
	return (filename);
}

char	*ft_addenvtoval(char *value, char *key)
{
	int		j;
	char	*tmp;

	j = -1;
	while (g_gob.env[++j])
	{
		if (ft_strncmp(g_gob.env[j], key, ft_strlen(key)) == 0
			&& g_gob.env[j][ft_strlen(key)] == '=')
		{
			tmp = ft_strdup(g_gob.env[j] + ft_strlen(key) + 1);
			value = ft_strjoin(value, tmp);
			return (value);
		}
	}
	return (value);
}

char	*ft_expand_env(char *line)
{
	char	*value;
	char	*key;
	int		i;

	i = 0;
	key = ft_strdup("");
	value = ft_strdup("");
	while (line[i] && line[i] != '$')
	{
		value = ft_strjoin_char(value, line[i]);
		i++;
	}
	if (line[i] == '$')
	{
		if (line[i + 1] == '?' && !ft_isprint(line[i + 2]))
			value = ft_strjoin_char(value, g_gob.ex_status + '0');
		while (ft_isprint(line[i + 1]))
			key = ft_strjoin_char(key, line[++i]);
		i++;
	}
	value = ft_addenvtoval(value, key);
	while (line[i])
		value = ft_strjoin_char(value, line[i++]);
	return (free(key), value);
}

void	ft_heredoc(char *del, char *filename)
{
	char	*line;
	char	*tmp;
	int		fd;

	fd = open(filename, O_CREAT | O_RDWR, 0644);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, del, ft_strlen(del)))
			break ;
		if (ft_strchr(line, '$'))
		{
			tmp = ft_expand_env(line);
			free(line);
			line = tmp;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	free(filename);
	close(fd);
}
