/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 09:45:23 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 02:58:52 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**update_env(char *key, char **env)
{
	char	**u_env;
	int		i;
	int		j;

	u_env = malloc(sizeof(char *) * ft_tabsize(env));
	if (!u_env)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) != 0)
		{
			u_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	u_env[j] = NULL;
	return (u_env);
}

static void	ft_unsetenv(char *key, char type)
{
	char	**u_env;
	char	**env;

	if (type == 'e')
		env = g_gob.env;
	else
		env = g_gob.s_env;
	u_env = update_env(key, env);
	if (!u_env)
		return ;
	dp_free(env);
	if (type == 'e')
		g_gob.env = u_env;
	else
		g_gob.s_env = u_env;
}

void	ft_unset(t_command *cmd)
{
	int	i;

	i = 1;
	if (!cmd->items[i])
		return ;
	while (cmd->items[i])
	{
		if (is_keyexist(cmd->items[i], g_gob.env))
			ft_unsetenv(cmd->items[i], 'e');
		if (is_keyexist(cmd->items[i], g_gob.s_env))
			ft_unsetenv(cmd->items[i], 's');
		i++;
	}
}
