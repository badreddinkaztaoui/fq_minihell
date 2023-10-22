/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 01:11:38 by bkaztaou          #+#    #+#             */
/*   Updated: 2022/11/10 02:07:08 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_calloc(1, sizeof(char)));
	if (len > (s_len - start))
		len = s_len - start;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_memmove(str, s + start, len);
	*(str + len) = '\0';
	return (str);
}
