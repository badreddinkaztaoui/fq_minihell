/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 07:03:31 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 02:56:45 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ctrl_d(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	ctrl_c(int num)
{
	(void)num;
	g_gob.ex_status = 1;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_(int num)
{
	(void)num;
	ft_putstr_fd("\n", 1);
	exit(1);
}
