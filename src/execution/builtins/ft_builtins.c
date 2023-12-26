/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:23:12 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/26 16:04:39 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(command, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(command, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(command, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(command, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(command, "exit", 4) == 0)
		return (1);
	return (0);
}

void	ft_builtins(t_command *cmd)
{
	if (ft_strncmp(cmd->items[0], "echo", 4) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd->items[0], "cd", 2) == 0)
		ft_cd(cmd);
	else if (ft_strncmp(cmd->items[0], "pwd", 3) == 0)
		ft_pwd(cmd);
	else if (ft_strncmp(cmd->items[0], "export", 6) == 0)
	{
		if (ft_export(cmd))
			return ;
	}
	else if (ft_strncmp(cmd->items[0], "unset", 5) == 0)
		ft_unset(cmd);
	else if (ft_strncmp(cmd->items[0], "env", 3) == 0)
		ft_env(cmd);
	else if (ft_strncmp(cmd->items[0], "exit", 4) == 0)
		ft_exit(cmd);
}
