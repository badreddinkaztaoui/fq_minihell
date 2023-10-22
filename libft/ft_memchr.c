/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:05:27 by bkaztaou          #+#    #+#             */
/*   Updated: 2022/11/04 17:57:01 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*ss;

	i = 0;
	cc = c;
	ss = (unsigned char *)s;
	while (i < n)
	{
		if (*(ss + i) == cc)
			return ((unsigned char *)(s + i));
		i++;
	}
	return (NULL);
}
