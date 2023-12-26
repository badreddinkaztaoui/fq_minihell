/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 09:46:02 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/26 17:33:36 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_putenv(char *key, char *value)
{
	char	**env;

	env = g_gob.env;
	while (*env)
	{
		if (!ft_strncmp(*env, key, ft_strlen(key)))
		{
			free(*env);
			*env = ft_strjoin(key, value);
			return ;
		}
		env++;
	}
	free(key);
	free(value);
}

void	ft_setenv(char *item)
{
	char	**tmp;
	char	*key;
	char	*value;

	tmp = ft_split(item, '=');
	key = ft_strdup(tmp[0]);
	key = ft_strjoin_char(key, '=');
	if (!tmp[1])
		value = ft_strdup("");
	else
		value = ft_strdup(tmp[1]);
	ft_putenv(key, value);
	dp_free(tmp);
}

int	export_err(t_command *cmd, int i)
{
	if (cmd->items[i] && !is_valid_key(cmd->items[i]))
	{
		ft_putstr_fd("minishell: export: ", cmd->out_fd);
		ft_putstr_fd(cmd->items[i], cmd->out_fd);
		ft_putstr_fd(" not a valid identifier\n", cmd->out_fd);
		return (1);
	}
	return (0);
}

int	ft_export(t_command *cmd)
{
	int	i;

	if (cmd->index == 1)
		return (export_print(), 0);
	i = 1;
	while (i < cmd->index && !ft_strncmp(cmd->items[i], "\0", 1))
		i++;
	if (i == cmd->index)
		return (export_print(), 0);
	while (i < cmd->index)
	{
		if (!ft_strncmp(cmd->items[i], "\0", 1))
		{
			i++;
			continue ;
		}
		else if (export_err(cmd, i))
			return (1);
		ft_setenv(cmd->items[i]);
		i++;
	}
	return (0);
}
