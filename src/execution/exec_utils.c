/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:37:21 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 02:17:07 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_close_files(t_command *cmd, t_command *tmp)
{
	while (tmp && tmp->index <= cmd->index)
	{
		if (tmp->index == cmd->index)
		{
			if (tmp->in_fd > 2)
				dup2(tmp->in_fd, 0);
		}
		else if (tmp->index + 1 == cmd->index)
		{
			close(tmp->fds[1]);
			if (tmp->in_fd == 0)
				dup2(tmp->fds[0], 0);
			if (tmp->in_fd > 2)
				dup2(tmp->in_fd, 0);
		}
		else
		{
			close(tmp->fds[0]);
			close(tmp->fds[1]);
		}
		tmp = tmp->next;
	}
}

void	ft_close_all(t_command *cmd, t_command *tmp)
{
	while (tmp && tmp->index <= cmd->index)
	{
		if (tmp->fds[0] > 2)
			close(tmp->fds[0]);
		if (tmp->fds[1] > 2)
			close(tmp->fds[1]);
		tmp = tmp->next;
	}
}

void	throw_error(t_command *cmd)
{
	if (!cmd->items || !ft_strlen(cmd->items[0]))
		ft_cmd_not_found("");
	if (cmd->items && cmd->items[0])
		ft_cmd_not_found(cmd->items[0]);
	else
		exit(0);
}