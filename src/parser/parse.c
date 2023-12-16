/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:35:39 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/16 14:02:59 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_token_to_command(t_command *command, char *item)
{
	command->items = ft_realloc(command->items, sizeof(char *)
			* (command->index + 1));
	command->items[command->index]
		= malloc(sizeof(char) * (ft_strlen(item) + 1));
	if (!command->items[command->index])
		return ;
	ft_strlcpy(command->items[command->index], item, ft_strlen(item) + 1);
	command->index++;
}

void	parse_cmd(t_command **cmd, t_parser *parser, char **env)
{
	if (parser->next_token->type == PIPE)
	{
		(*cmd)->next = init_command();
		*cmd = (*cmd)->next;
	}
	if (is_redirection(parser->prev_token))
		handle_redirection(cmd, parser, env);
}

int	is_valid_start(t_parser *parser)
{
	if (!parser->prev_token
		&& (is_iofiles(parser->next_token)
			|| parser->next_token->type == PIPE))
	{
		ft_unexpected_token(parser->next_token->value);
		free_token(parser->next_token);
		return (0);
	}
	return (1);
}

void	parse(t_lexer *lexer, char **env, t_parser *parser)
{
	t_command	*command;

	init_parser(parser);
	command = parser->command;
	parser->next_token = lexer_get_next_token(lexer, env);
	while (parser->next_token->type != END)
	{
		if (!is_valid_start(parser))
			return ;
		if (can_add_cmd(parser))
			add_token_to_command(command, parser->next_token->value);
		if (parser->prev_token)
			free_token(parser->prev_token);
		parser->prev_token = clone_token(parser->next_token);
		free_token(parser->next_token);
		parser->next_token = lexer_get_next_token(lexer, env);
		if (!is_valid_cmd(parser))
			return ;
		parse_cmd(&command, parser, env);
	}
	free_token(parser->prev_token);
	free_token(parser->next_token);
}
