/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 02:09:38 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/12 19:20:54 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_hd_process(char *del, char *filename, char **env)
{
	int		id;
	int		status;

	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == -1)
		return (free(filename), 1);
	if (id == 0)
	{
		signal(SIGINT, ctrl_handler);
		ft_heredoc(del, filename, env);
		exit(0);
	}
	waitpid(id, &status, 0);
	if (WEXITSTATUS(status))
		return (1);
	return (0);
}

int	heredoc(char *del, t_command **cmd, char **env)
{
	char	*filename;
	char	*tmp;

	signal(SIGQUIT, SIG_IGN);
	filename = ft_genname();
	tmp = ft_strdup("/tmp/tmp_");
	filename = ft_strjoin(tmp, filename);
	if (ft_hd_process(del, filename, env))
	{
		unlink(filename);
		free(filename);
		return (1);
	}
	(*cmd)->in_fd = open(filename, O_RDONLY, 0644);
	if ((*cmd)->in_fd == -1)
		return (1);
	unlink(filename);
	free(filename);
	return (0);
}