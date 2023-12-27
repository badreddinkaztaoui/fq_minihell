/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:39:15 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/27 17:57:18 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_exitnum(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->items[1][i])
	{
		if (!ft_isdigit(cmd->items[1][i]))
		{
			ft_putstr_fd("exit: ", cmd->out_fd);
			ft_putstr_fd(cmd->items[1], cmd->out_fd);
			ft_putstr_fd(": numeric argument required\n", cmd->out_fd);
			exit(255);
		}
		i++;
	}
	if (cmd->items[2])
	{
		ft_putstr_fd("exit: too many arguments\n", cmd->out_fd);
		return ;
	}
	else
		exit(ft_atoi(cmd->items[1]));
}

void	ft_exit(t_command *cmd)
{
	int	len;

	len = ft_tabsize(cmd->items);
	ft_putendl_fd("exit", cmd->out_fd);
	if (len >= 2)
		ft_exitnum(cmd);
	else if (len == 1)
		exit(g_gob.ex_status);
}