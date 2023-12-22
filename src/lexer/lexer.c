/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:23:16 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/22 23:16:01 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->line))
	{
		lexer->i++;
		lexer->c = lexer->line[lexer->i];
	}
}

t_token	*lexer_advance_with(t_token *token, t_lexer *lexer)
{
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		if (ft_iswp(lexer->c))
			lexer_advance(lexer);
		if (ft_isprint(lexer->c))
			return (lexer_collect_cmd(lexer));
		if (lexer->c == '|')
			return (lexer_advance_with(
					init_token(ft_strdup("|"), PIPE), lexer));
		if (lexer->c == '\'')
			return (lexer_collect_squote(lexer));
		if (lexer->c == '\"')
			return (lexer_collect_dquote(lexer));
		if (lexer->c == '<')
			return (lexer_collect_larrow(lexer));
		if (lexer->c == '>')
			return (lexer_collect_rarrow(lexer));
	}
	return (init_token(ft_strdup("EOF"), END));
}
