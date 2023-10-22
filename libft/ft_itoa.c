/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 02:31:57 by bkaztaou          #+#    #+#             */
/*   Updated: 2022/11/05 04:07:09 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_num_len(int n)
{
	size_t	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			num_len;
	unsigned int	num;

	num = n;
	num_len = ft_num_len(n);
	str = ft_calloc(num_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		num = -n;
		str[0] = '-';
	}
	if (num == 0)
		str[0] = '0';
	str[num_len] = '\0';
	while (num != 0)
	{
		str[num_len - 1] = num % 10 + '0';
		num = num / 10;
		num_len--;
	}
	return (str);
}
