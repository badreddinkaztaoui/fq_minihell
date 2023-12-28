/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:11:46 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 02:55:17 by bkaztaou         ###   ########.fr       */
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

char	*lexer_collect_dollar(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	if (lexer->c == '?')
	{
		value = ft_strdup("");
		value = ft_strjoin_char(value, g_gob.ex_status + '0');
		lexer_advance(lexer);
		return (value);
	}
	value = ft_strdup("");
	value = ft_strjoin(value, get_env_val(lexer));
	return (value);
}

char	*lexer_collect_squote(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	value = ft_strdup("");
	value = q_expand(lexer, value, '\'');
	lexer_advance(lexer);
	if (!value)
		return (NULL);
	return (value);
}

char	*lexer_collect_dquote(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	value = ft_strdup("");
	value = q_expand(lexer, value, '\"');
	lexer_advance(lexer);
	if (!value)
		return (NULL);
	return (value);
}
