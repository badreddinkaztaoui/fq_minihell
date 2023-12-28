/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getkey.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 00:12:55 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 02:55:51 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getkey(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = ft_strdup("");
	while (str[i] && str[i] != '=')
	{
		key = ft_strjoin_char(key, str[i]);
		i++;
	}
	return (key);
}
