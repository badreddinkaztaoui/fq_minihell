/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 22:47:46 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/27 17:55:50 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_updateenv(char *value, char *key)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_gob.env[i])
	{
		if (ft_strncmp(g_gob.env[i], key, ft_strlen(key)) == 0)
		{
			tmp = ft_strdup(g_gob.env[i]);
			free(g_gob.env[i]);
			g_gob.env[i] = ft_strdup(value);
			free(tmp);
			return ;
		}
		i++;
	}
}

void	ft_updatepwd(char *pwd)
{
	char	*tmp;
	char	*new_pwd;

	tmp = ft_strdup("PWD=");
	tmp = ft_strjoin(tmp, pwd);
	new_pwd = ft_strdup(tmp);
	free(tmp);
	ft_updateenv(new_pwd, "PWD");
	free(new_pwd);
}

void	ft_updateoldpwd(char *pwd)
{
	char	*tmp;
	char	*new_pwd;

	tmp = ft_strdup("OLDPWD=");
	tmp = ft_strjoin(tmp, pwd);
	new_pwd = ft_strdup(tmp);
	free(tmp);
	ft_updateenv(new_pwd, "OLDPWD");
	free(new_pwd);
}

void	ft_cd(t_command *cmd)
{
	char	*path;
	char	*o_pwd;
	char	*c_pwd;
	int		len;

	len = ft_tabsize(cmd->items);
	if (len == 1 || ft_strncmp(cmd->items[1], "~", 1) == 0)
		path = getenv("HOME");
	else
	{
		path = cmd->items[1];
		o_pwd = getcwd(NULL, 0);
		if (o_pwd)
			ft_updateoldpwd(o_pwd);
		if (chdir(path) == -1)
		{
			perror(path);
			g_gob.ex_status = 1;
		}
		c_pwd = getcwd(NULL, 0);
		if (c_pwd)
			ft_updatepwd(c_pwd);
	}
	g_gob.ex_status = 0;
}
