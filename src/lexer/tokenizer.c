/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:11:46 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/22 23:44:13 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*lexer_collect_larrow(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	if (lexer->c == '<')
	{
		lexer_advance(lexer);
		value = ft_strdup("<<");
		return (init_token(value, HEREDOC));
	}
	value = ft_strdup("<");
	return (init_token(value, REDIR_IN));
}

t_token	*lexer_collect_rarrow(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	if (lexer->c == '>')
	{
		lexer_advance(lexer);
		value = ft_strdup(">>");
		return (init_token(value, REDIR_APPEND));
	}
	value = ft_strdup(">");
	return (init_token(value, REDIR_OUT));
}

t_token	*lexer_collect_cmd(t_lexer *lexer)
{
	char	*value;

	value = ft_strdup("");
	value = c_expand(lexer, value);
	if (!value)
		return (init_token(ft_strdup(""), END));
	return (init_token(value, CMD));
}

t_token	*lexer_collect_squote(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	value = ft_strdup("");
	value = q_expand(lexer, value, '\'');
	lexer_advance(lexer);
	if (!value)
		return (init_token(ft_strdup(""), END));
	return (init_token(value, CMD));
}

t_token	*lexer_collect_dquote(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	value = ft_strdup("");
	value = q_expand(lexer, value, '\"');
	lexer_advance(lexer);
	if (!value)
		return (init_token(ft_strdup(""), END));
	return (init_token(value, CMD));
}
