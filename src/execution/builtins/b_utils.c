/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:02:35 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/26 15:40:04 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_valid_key(char *command)
{
	int	i;

	i = 0;
	if (!ft_isalpha(command[i]) && command[i] != '_')
		return (0);
	while (command[i])
	{
		if (!ft_isalnum(command[i])
			&& command[i] != '_' && command[i] != '='
			&& command[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

char	**clone_env(void)
{
	char	**envc;
	char	**envp;
	int		i;

	envp = g_gob.env;
	envc = malloc(sizeof(char *) * (ft_tabsize(g_gob.env) + 1));
	if (!envc)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envc[i] = ft_strdup(envp[i]);
		i++;
	}
	envc[i] = NULL;
	return (envc);
}

void	sort_by_key(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strncmp(envp[i], envp[j],
					ft_strlen(envp[i])) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	export_print(void)
{
	char	**env;

	env = clone_env();
	sort_by_key(env);
	while (*env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(*env, 1);
		ft_putstr_fd("\n", 1);
		env++;
	}
}
