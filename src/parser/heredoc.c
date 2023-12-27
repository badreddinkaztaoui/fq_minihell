/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 02:09:38 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/27 14:52:02 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	h_process(t_token *del, char *filename)
{
	int		id;
	int		status;

	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == -1)
		return (free(filename), 1);
	if (id == 0)
	{
		signal(SIGINT, ctrl_);
		ft_heredoc(del, filename);
		exit(0);
	}
	waitpid(id, &status, 0);
	if (WEXITSTATUS(status))
		return (1);
	return (0);
}

int	heredoc(t_token *del, t_command **cmd)
{
	char	*filename;
	char	*tmp;

	signal(SIGQUIT, SIG_IGN);
	filename = ft_genname();
	tmp = ft_strdup("/tmp/tmp_");
	filename = ft_strjoin(tmp, filename);
	if (h_process(del, filename))
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
