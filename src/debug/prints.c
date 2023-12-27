/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:03:48 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/27 17:54:38 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_tokens(t_lexer *lexer)
{
	t_token	*token;

	printf("|-----------------|-----------------|\n");
	printf("|      value      |       type      |\n");
	printf("|-----------------|-----------------|\n");
	token = lexer_get_next_token(lexer);
	while (token->type != END)
	{
		printf("|%17s|%17d|\n", token->value, token->type);
		free(token->value);
		free(token);
		token = lexer_get_next_token(lexer);
	}
	printf("|-----------------|-----------------|\n");
	free(token->value);
	free(token);
}

void	print_command(t_command *command)
{
	int	i;

	while (command)
	{
		i = 0;
		while (command->items[i])
		{
			printf("items[%d]: %s\n", i, command->items[i]);
			i++;
		}
		printf("in_fd: %d\n", command->in_fd);
		printf("out_fd: %d\n", command->out_fd);
		command = command->next;
	}
}
