/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 21:19:27 by bkaztaou          #+#    #+#             */
/*   Updated: 2022/11/04 23:08:37 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	ft_isorange(unsigned long long result, int sign)
{
	if (result > LLONG_MAX && sign == -1)
		return (0);
	if (result > LLONG_MAX && sign == 1)
		return (-1);
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	size_t				i;
	int					sign;
	unsigned long long	result;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_iswspace(str[i]))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		result = result * 10 + str[i++] - '0';
	return (ft_isorange(result, sign));
}
