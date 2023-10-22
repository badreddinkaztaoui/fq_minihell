/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:55:53 by bkaztaou          #+#    #+#             */
/*   Updated: 2022/11/11 03:24:29 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		found;

	i = -1;
	found = 1;
	if (!ft_strlen(needle))
		return ((char *)haystack);
	while (++i < len && haystack[i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			k = i;
			found = 1;
			while (haystack[k] && needle[j] && k < len)
				if (haystack[k++] != needle[j++])
					found = 0;
			if (found && needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
	}
	return (NULL);
}
