/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:38:29 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 02:40:22 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_cmds(t_command *cmd)
{
	int		i;
	char	**paths;
	char	*command;

	i = 0;
	if (cmd->items && access(cmd->items[0], X_OK) == 0)
		execve(cmd->items[0], cmd->items, g_gob.env);
	else if (cmd->items && is_keyexist("PATH", g_gob.env))
	{
		paths = ft_split(ft_geteval("PATH"), ':');
		while (paths[i])
		{
			paths[i] = ft_strjoin_char(paths[i], '/');
			command = ft_strjoin(paths[i], ft_strdup(cmd->items[0]));
			if (access(command, X_OK) == 0)
				execve(command, cmd->items, g_gob.env);
			free(command);
			i++;
		}
		free(paths);
	}
	throw_error(cmd);
}

void	execute_pipes(t_command *cmd, t_command *tmp)
{
	int	pid;

	(void)tmp;
	pipe(cmd->fds);
	pid = fork();
	if (pid == 0)
	{
		close(cmd->fds[0]);
		if (cmd->in_fd == 0 && cmd->index > 0)
			cmd->in_fd = cmd->fds[0];
		dup2(cmd->in_fd, 0);
		if (cmd->out_fd == 1)
		{
			cmd->out_fd = cmd->fds[1];
			dup2(cmd->fds[1], 1);
		}
		else if (cmd->out_fd > 2)
			dup2(cmd->out_fd, 1);
		ft_close_files(cmd, tmp);
		if (is_builtin(cmd->items[0]))
			ft_builtins(cmd);
		else
			run_cmds(cmd);
		exit(0);
	}
}

void	execute_one_cmd(t_command *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->out_fd > 2)
			dup2(cmd->out_fd, 1);
		if (cmd->in_fd > 2)
			dup2(cmd->in_fd, 0);
		run_cmds(cmd);
	}
	else
	{
		if (cmd->out_fd > 2)
			close(cmd->out_fd);
		if (cmd->in_fd > 2)
			close(cmd->in_fd);
	}
	wait(&g_gob.ex_status);
	g_gob.ex_status = WEXITSTATUS(g_gob.ex_status);
}

void	execute_last_cmd(t_command *cmd, t_command *tmp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_close_files(cmd, tmp);
		if (cmd->out_fd > 2)
			dup2(cmd->out_fd, 1);
		else if (cmd->out_fd == 1)
			dup2(1, cmd->out_fd);
		if (is_builtin(cmd->items[0]))
			ft_builtins(cmd);
		else
			run_cmds(cmd);
		exit(0);
	}
	ft_close_all(cmd, tmp);
	while (wait(NULL) != -1)
		;
}

void	execute_cmds(t_command *cmd, t_command *tmp, int size)
{
	
	if (size > 1)
	{
		if (cmd->index != size - 1)
			execute_pipes(cmd, tmp);
		else
			execute_last_cmd(cmd, tmp);
	}
	else
		execute_one_cmd(cmd);
}