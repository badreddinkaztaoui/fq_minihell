/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 23:12:20 by bkaztaou          #+#    #+#             */
/*   Updated: 2022/11/05 00:51:02 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (count != 0 && size > (SIZE_MAX / count))
		return (NULL);
	str = malloc(size * count);
	if (!str)
		return (NULL);
	ft_bzero(str, (count * size));
	return (str);
}
