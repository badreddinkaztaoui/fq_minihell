/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:35:39 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/10 03:22:19 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void add_token_to_command(t_command *command, char *item)
{
	command->items = ft_realloc(command->items, sizeof(char *) * (command->index + 1));
	command->items[command->index] = malloc(sizeof(char) * (ft_strlen(item) + 1));
	if (!command->items[command->index])
		return;
	ft_strlcpy(command->items[command->index], item, ft_strlen(item) + 1);
	command->index++;
}
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

void ft_heredoc(char *delimiter)
{
	char *line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			free(line);
			break;
		}
		free(line);
	}
}

void parse(t_lexer *lexer, char **env, t_parser *parser)
{
	t_command 	*command;
	t_command 	*tmp;

	init_parser(parser);
	command = parser->command;
	tmp = command;
	parser->next_token = lexer_get_next_token(lexer, env);
	parser->prev_token = parser->next_token;
	while (parser->next_token->type != END)
	{
		
		if (parser->next_token->type == CMD)
			add_token_to_command(command, parser->next_token->value);
		else if (parser->next_token->type == PIPE)
		{
			if (!is_valid_pipe_pos(parser))
				return;
			command->next = init_command();
			command = command->next;
		}
		if (!is_valid_end_cmd(parser))
			return;
		free_token(parser->next_token);
		parser->next_token = lexer_get_next_token(lexer, env);
	}
	free_token(parser->next_token);
	print_command(tmp);
}
