/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 09:45:23 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/26 10:22:36 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_unsetenv(char *key)
{
	char	**env;
	char	**u_env;
	int		i;
	int		j;

	env = g_gob.env;
	u_env = malloc(sizeof(char *) * ft_tabsize(env));
	if (!u_env)
		return ;
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
	free(env);
	g_gob.env = u_env;
}

void	ft_unset(t_command *cmd)
{
	int	i;

	i = 1;
	if (!cmd->items[i])
		return ;
	while (i < cmd->index)
	{
		if (getenv(cmd->items[i]))
			ft_unsetenv(cmd->items[i]);
		i++;
	}
}