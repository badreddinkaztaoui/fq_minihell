/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:13:01 by bkaztaou          #+#    #+#             */
/*   Updated: 2022/11/04 17:57:10 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = dst;
	s = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (s < d && (s + len) > d)
		while (len >= 0 && len--)
			*(d + len) = *(s + len);
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
