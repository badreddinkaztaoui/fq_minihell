/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:32:09 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/11/21 19:34:31 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
