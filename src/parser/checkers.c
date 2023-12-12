/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:26:24 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/10 22:09:52 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int is_valid_pipe_pos(t_parser *parser)
{
	if (!parser->prev_token || parser->prev_token->type == PIPE)
	{
		ft_unexpected_token(parser->next_token->value);
		return (0);
	}
	return (1);
}

int is_valid_end_cmd(t_parser *parser)
{
	if (parser->next_token->type == END &&
		(parser->prev_token->type == PIPE || parser->prev_token->type == REDIR_IN || parser->prev_token->type == REDIR_OUT || parser->prev_token->type == REDIR_APPEND || parser->prev_token->type == HEREDOC))
		return (ft_unexpected_token(parser->prev_token->value), 0);
	return (1);
}
