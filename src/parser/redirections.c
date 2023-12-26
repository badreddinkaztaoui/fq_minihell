/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:28:30 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/26 01:54:32 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_in(t_command **cmd, t_parser *pars)
{
	int	fd;

	fd = open(pars->next_token->value, O_RDONLY, 0677);
	if (fd == -1)
	{
		ft_nofile(pars->next_token->value);
		return (1);
	}
	(*cmd)->in_fd = fd;
	return (0);
}

int	redir_out(t_command **cmd, t_parser *pars)
{
	int	fd;

	fd = open(pars->next_token->value, O_WRONLY | O_CREAT | O_TRUNC, 0677);
	if (fd == -1)
	{
		ft_nofile(pars->next_token->value);
		return (1);
	}
	(*cmd)->out_fd = fd;
	return (0);
}

int	redir_append(t_command **cmd, t_parser *pars)
{
	int	fd;

	fd = open(pars->next_token->value, O_WRONLY | O_CREAT | O_APPEND, 0677);
	if (fd == -1)
	{
		ft_nofile(pars->next_token->value);
		return (1);
	}
	(*cmd)->out_fd = fd;
	return (0);
}

int	handle_redirection(t_command **cmd, t_parser *pars)
{
	int	status;

	status = 0;
	if (pars->prev_token->type == HEREDOC)
		status = heredoc(pars->next_token, cmd);
	if (pars->prev_token->type == REDIR_IN)
		status = redir_in(cmd, pars);
	if (pars->prev_token->type == REDIR_OUT)
		status = redir_out(cmd, pars);
	if (pars->prev_token->type == REDIR_APPEND)
		status = redir_append(cmd, pars);
	return (status);
}
