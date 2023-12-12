/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:35:39 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/12 19:31:17 by bkaztaou         ###   ########.fr       */
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

void	handle_redirection(t_command **command, t_parser *parser, char **env)
{
	if (parser->prev_token->type == HEREDOC)
		heredoc(parser->next_token->value, command, env);
}

void	parse_cmd_by_type(t_command **command, t_parser *parser, char **env)
{
	if (parser->next_token->type == CMD)
		add_token_to_command(*command, parser->next_token->value);
	else if (parser->next_token->type == PIPE)
	{
		(*command)->next = init_command();
		*command = (*command)->next;
	}
	if (is_redirection(parser->prev_token))
		handle_redirection(command, parser, env);
}

void parse(t_lexer *lexer, char **env, t_parser *parser)
{
	t_command 	*command;
	t_command 	*tmp;

	init_parser(parser);
	command = parser->command;
	tmp = command;
	parser->next_token = lexer_get_next_token(lexer, env);
	while (parser->next_token->type != END)
	{
		if (is_start_w_pipe(parser))
			return ;
		if (parser->prev_token)
			free_token(parser->prev_token);
		parser->prev_token = clone_token(parser->next_token);
		free_token(parser->next_token);
		parser->next_token = lexer_get_next_token(lexer, env);
		if (!is_valid_cmd(parser))
			return ;
		parse_cmd_by_type(&command, parser, env);
	}
	free_token(parser->prev_token);
	free_token(parser->next_token);
	print_command(tmp);
}
