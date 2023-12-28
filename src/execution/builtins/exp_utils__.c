/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils__.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:12:21 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 06:14:01 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_getenv(char *key, char *val, int has_equal)
{
	char	*c_key;
	char	*c_val;

	c_key = ft_strdup(key);
	if (has_equal)
		c_key = ft_strjoin_char(c_key, '=');
	c_val = ft_strdup(val);
	return (ft_strjoin(c_key, c_val));
}

int	is_keyexist(char *key, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
			return (1);
		i++;
	}
	return (0);
}

char	**ft_tabjoin(char **envp, char *env)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (ft_tabsize(envp) + 2));
	if (!tmp)
		return (NULL);
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = ft_strdup(env);
	tmp[i + 1] = NULL;
	free(envp);
	return (tmp);
}

void	ft_export_nxt(t_command *cmd)
{
	int	i;

	i = 0;
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
}
