/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:22:39 by bkaztaou          #+#    #+#             */
/*   Updated: 2022/11/04 21:18:28 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	if (!dst && dstsize == 0)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize < dst_len + 1)
		return (src_len + dstsize);
	if (dstsize > dst_len + 1)
	{
		i = ft_strlen(dst);
		j = 0;
		while (i < dstsize - 1 && src[j])
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	return (src_len + dst_len);
}
