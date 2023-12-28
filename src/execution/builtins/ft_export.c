/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 09:46:02 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 00:16:46 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_update_env(char *key, char *val, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
		{
			free(envp[i]);
			envp[i] = ft_getenv(key, val, 1);
			break ;
		}
		i++;
	}
}

void	ft_putenv(char *key, char *value, int has_equal)
{
	char	*envp;

	envp = ft_getenv(key, value, has_equal);
	if (is_keyexist(key, g_gob.env))
		ft_update_env(key, value, g_gob.env);
	if (is_keyexist(key, g_gob.s_env))
		ft_update_env(key, value, g_gob.s_env);
	if (!is_keyexist(key, g_gob.env) && has_equal)
		g_gob.env = ft_tabjoin(g_gob.env, envp);
	if (!is_keyexist(key, g_gob.s_env))
		g_gob.s_env = ft_tabjoin(g_gob.s_env, envp);
	free(envp);
}

void	ft_setenv(char *item)
{
	char	*key;
	char	*value;
	int		has_equal;
	int		i;

	i = 0;
	has_equal = 0;
	key = ft_strdup("");
	value = ft_strdup("");
	while (item[i] && item[i] != '=')
	{
		key = ft_strjoin_char(key, item[i]);
		i++;
	}
	if (item[i] == '=')
	{
		has_equal = 1;
		i++;
	}
	while (item[i])
		value = ft_strjoin_char(value, item[i++]);
	ft_putenv(key, value, has_equal);
	free(key);
	free(value);
}

int	ft_export(t_command *cmd)
{
	int		i;
	int		len;
	char	*key;

	len = ft_tabsize(cmd->items);
	if (len == 1)
		return (export_print(), 0);
	i = 1;
	while (cmd->items[i] && !ft_strncmp(cmd->items[i], "\0", 1))
		i++;
	if (i == len)
		return (export_print(), 0);
	key = ft_getkey(cmd->items[i]);
	if (export_err(cmd, key, i))
		return (1);
	while (cmd->items[i])
	{
		if (!ft_strncmp(cmd->items[i], "\0", 1))
		{
			i++;
			continue ;
		}
		ft_setenv(cmd->items[i]);
		i++;
	}
	return (0);
}
