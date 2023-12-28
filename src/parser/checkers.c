/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:26:24 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 00:36:43 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_iofiles(t_token *token)
{
	if (token->type == REDIR_OUT
		|| token->type == REDIR_APPEND)
		return (1);
	return (0);
}

int	is_redirection(t_token *token)
{
	if (is_iofiles(token) || token->type == REDIR_IN
		|| token->type == HEREDOC)
		return (1);
	return (0);
}

int	is_not_cmd(t_token *token)
{
	if (token->type == PIPE || is_redirection(token))
		return (1);
	return (0);
}

int	can_add_cmd(t_parser *parser)
{
	if (parser->next_token->type != CMD)
		return (0);
	else if (parser->prev_token
		&& (is_redirection(parser->prev_token)
			&& parser->next_token->type == CMD))
		return (0);
	return (1);
}

int	is_valid_cmd(t_parser *parser)
{
	if ((parser->next_token->type == END && is_not_cmd(parser->prev_token))
		|| (parser->prev_token->type == PIPE
			&& parser->next_token->type == PIPE)
		|| (parser->prev_token && is_redirection(parser->prev_token)
			&& is_not_cmd(parser->next_token)))
	{
		ft_unexpected_token(parser->prev_token->value);
		free_token(parser->next_token);
		free_token(parser->prev_token);
		free_command(parser);
		return (0);
	}
	return (1);
}
