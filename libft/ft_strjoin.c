/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 01:01:56 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/10/21 13:34:54 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *stash, char *buff)
{
	int		i;
	int		j;
	char	*temp;

	if (!stash && !buff)
		return (NULL);
	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	temp = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buff) + 1));
	if (!temp)
		return (NULL);
	i = -1;
	while (stash[++i])
		temp[i] = stash[i];
	j = -1;
	while (buff[++j])
		temp[i++] = buff[j];
	temp[i] = '\0';
	return (free(stash), free(buff), temp);
}
