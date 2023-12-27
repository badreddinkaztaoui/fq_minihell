/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:13:52 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/27 20:36:02 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execution(t_command *cmd)
{
	int			size;
	t_command	*tmp;

	tmp = cmd;
	if (!cmd->items)
		return ;
	size = ft_listsize(cmd);
	if (cmd && size == 1 && is_builtin(cmd->items[0]))
		ft_builtins(cmd);
	else
	{
		while (cmd)
		{
			execute_cmds(cmd, tmp, size);
			cmd = cmd->next;
		}
	}
}