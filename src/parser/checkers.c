/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:26:24 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/12 19:27:19 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redirection(t_token *token)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_APPEND || token->type == HEREDOC)
		return (1);
	return (0);
}

int	is_shelltoken(t_token *token)
{
	if (token->type == PIPE || is_redirection(token))
		return (1);
	return (0);
}

int	is_start_w_pipe(t_parser *parser)
{
	if (!parser->prev_token && parser->next_token->type == PIPE)
	{
		ft_unexpected_token(parser->next_token->value);
		free_token(parser->next_token);
		return (1);
	}
	return (0);
}

int is_valid_cmd(t_parser *parser)
{
	if (parser->next_token->type == END && is_shelltoken(parser->prev_token))
	{
		ft_unexpected_token(parser->prev_token->value);
		free_token(parser->prev_token);
		free_token(parser->next_token);
		return (0);
	}
	else if (parser->prev_token && is_shelltoken(parser->prev_token)
		&& is_shelltoken(parser->next_token))
	{
		ft_unexpected_token(parser->next_token->value);
		free_token(parser->prev_token);
		free_token(parser->next_token);
		return (0);
	}
	return (1);
}