/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:03:48 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/13 02:50:08 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_tokens(t_lexer *lexer, char **env)
{
	t_token	*token;

	printf("|-----------------|-----------------|\n");
	printf("|      value      |       type      |\n");
	printf("|-----------------|-----------------|\n");
	token = lexer_get_next_token(lexer, env);
	while (token->type != END)
	{
		printf("|%17s|%17d|\n", token->value, token->type);
		free(token->value);
		free(token);
		token = lexer_get_next_token(lexer, env);
	}
	printf("|-----------------|-----------------|\n");
	free(token->value);
	free(token);
}

void	print_command(t_command *command)
{
	while (command)
	{
		for (int i = 0; i < command->index; i++)
		{
			printf("|%-17s|\n", command->items[i]);
		}
		printf("in_fd: %d\n", command->in_fd);
		printf("out_fd: %d\n", command->out_fd);
		command = command->next;
	}
}
