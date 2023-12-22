/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:28:30 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/22 01:29:54 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redir_in(t_command **cmd, t_parser *pars)
{
	int	fd;

	fd = open(pars->next_token->value, O_RDONLY, 0677);
	if (fd == -1)
	{
		ft_nofile(pars->next_token->value);
		return ;
	}
	(*cmd)->in_fd = fd;
	unlink(pars->next_token->value);
}

void	redir_out(t_command **cmd, t_parser *pars)
{
	int	fd;

	fd = open(pars->next_token->value, O_WRONLY | O_CREAT | O_TRUNC, 0677);
	if (fd == -1)
	{
		ft_nofile(pars->next_token->value);
		return ;
	}
	(*cmd)->out_fd = fd;
	close((*cmd)->out_fd);
}

void	redir_append(t_command **cmd, t_parser *pars)
{
	int	fd;

	fd = open(pars->next_token->value, O_WRONLY | O_CREAT | O_APPEND, 0677);
	if (fd == -1)
	{
		ft_nofile(pars->next_token->value);
		return ;
	}
	if ((*cmd)->out_fd != 1)
		close((*cmd)->out_fd);
	(*cmd)->out_fd = fd;
	close((*cmd)->out_fd);
}

void	handle_redirection(t_command **cmd, t_parser *pars)
{
	if (pars->prev_token->type == HEREDOC)
		heredoc(pars->next_token->value, cmd);
	if (pars->prev_token->type == REDIR_IN)
		redir_in(cmd, pars);
	if (pars->prev_token->type == REDIR_OUT)
		redir_out(cmd, pars);
	if (pars->prev_token->type == REDIR_APPEND)
		redir_append(cmd, pars);
}
