/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:13:52 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/25 14:45:16 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execution(t_command *cmd)
{
	// int	i;
	int	size;

	// i = 0;
	size = ft_listsize(cmd);
	if (cmd && size == 1 && is_builtin(cmd->items[0]))
	{
		// ft_open_files(cmd);
		ft_builtins(cmd);
	}
}