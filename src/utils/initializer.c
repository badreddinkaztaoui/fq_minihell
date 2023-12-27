/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 04:18:19 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/27 18:55:46 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_envs(char **env)
{
	int		i;
	char	**tmp;

	i = 0;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return ;
	i = 0;
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = NULL;
	g_gob.env = tmp;
}

t_lexer	*init_lexer(char *line)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->line = line;
	lexer->line_len = ft_strlen(line);
	lexer->i = 0;
	lexer->c = line[lexer->i];
	return (lexer);
}

t_token	*init_token(char *value, t_types type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->in_fd = 0;
	command->out_fd = 1;
	command->items = NULL;
	command->next = NULL;
	command->index = 0;
	return (command);
}

void	init_parser(t_parser *parser)
{
	parser->command = init_command();
	parser->prev_token = NULL;
	parser->next_token = NULL;
}
