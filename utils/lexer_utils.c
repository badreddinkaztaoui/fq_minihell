/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:11:46 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/10/22 15:46:58 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

t_token *lexer_collect_cmd(t_lexer *lexer)
{
    char *value;
    t_token *token;

    value = ft_strdup("");
    while (lexer->c != '\0' && ft_isalpha(lexer->c))
    {
        value = ft_strjoin_char(value, lexer->c);
        lexer_advance(lexer);
    }
    token = init_token(value, CMD);
    return (token);
}

t_token	*lexer_collect_squote(t_lexer *lexer)
{
	char	*value;
	t_token	*token;

	value = ft_strdup("");
	lexer_advance(lexer);
	while (lexer->c != '\'' && lexer->c != '\0')
	{
		value = ft_strjoin_char(value, lexer->c);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	token = init_token(value, CMD);
	return (token);
}

char	*lexer_get_env_value(t_lexer *lexer, char **env)
{
	char	*value;
	char	*key;
	int		i;

	i = 0;
	key = ft_strdup("");
	while (lexer->c != '\0' && (ft_isalpha(lexer->c) || lexer->c == '_'))
	{
		key = ft_strjoin_char(key, lexer->c);
		lexer_advance(lexer);
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
		{
			value = ft_strdup(env[i] + ft_strlen(key) + 1);
			return (free(key), value);
		}
		i++;
	}
	return (ft_strdup(""));
}

t_token	*lexer_collect_dquote(t_lexer *lexer, char **env)
{
	char	*value;
	t_token	*token;

	value = ft_strdup("");
	lexer_advance(lexer);
	while (lexer->c != '\"' && lexer->c != '\0')
	{
		if (lexer->c == '$')
		{
			lexer_advance(lexer);
			value = ft_strjoin(value, lexer_get_env_value(lexer, env));
			continue ;
		}
		value = ft_strjoin_char(value, lexer->c);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	token = init_token(value, CMD);
	return (token);
}