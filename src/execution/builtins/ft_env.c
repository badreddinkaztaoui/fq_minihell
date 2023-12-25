/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:24:56 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/25 14:40:39 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	dp_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	ft_env(t_command *cmd)
{
	int		i;
	char	**envp;
	char	**tmp;

	i = 0;
	envp = g_gob.env;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		ft_putstr_fd(tmp[0], cmd->out_fd);
		ft_putstr_fd("=", cmd->out_fd);
		if (tmp[1])
			ft_putstr_fd(tmp[1], cmd->out_fd);
		ft_putstr_fd("\n", cmd->out_fd);
		dp_free(tmp);
		i++;
	}
	g_gob.ex_status = 0;
}