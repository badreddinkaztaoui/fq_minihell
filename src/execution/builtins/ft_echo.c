/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:55:08 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/26 01:49:28 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	has_n_flag(char *command)
{
	int i;

	i = 0;
	if (command[i] == '-')
	{
		i++;
		while (command[i])
		{
			if (command[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(t_command *cmd)
{
	int i;

	i = 1;
	while (i < cmd->index && has_n_flag(cmd->items[i]))
		i++;
	while (i < cmd->index)
	{
		ft_putstr_fd(cmd->items[i], cmd->out_fd);
		if (i + 1 < cmd->index)
			ft_putchar_fd(' ', cmd->out_fd);
		i++;
	}
	if (!has_n_flag(cmd->items[1]))
		ft_putchar_fd('\n', cmd->out_fd);
	g_gob.ex_status = 0;
}