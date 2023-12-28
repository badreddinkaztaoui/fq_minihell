/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_geteval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:36:40 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 02:55:55 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_geteval(char *key)
{
	char	**envp;
	int		i;

	i = 0;
	envp = g_gob.env;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
			return (ft_strdup(envp[i] + ft_strlen(key) + 1));
		i++;
	}
	return (NULL);
}
