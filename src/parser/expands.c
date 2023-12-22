/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 02:01:11 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/23 00:11:18 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_val(t_lexer *lexer)
{
	char	*value;
	char	*key;
	int		i;

	i = 0;
	key = ft_strdup("");
	while (lexer->c != '\0' && ft_isalnum(lexer->c))
	{
		key = ft_strjoin_char(key, lexer->c);
		lexer_advance(lexer);
	}
	if (ft_strlen(key) == 0)
		return (free(key), ft_strdup("$"));
	while (g_gob.env[i])
	{
		if (ft_strncmp(g_gob.env[i], key, ft_strlen(key)) == 0)
		{
			value = ft_strdup(g_gob.env[i] + ft_strlen(key) + 1);
			return (free(key), value);
		}
		i++;
	}
	return (free(key), ft_strdup(""));
}

char	*q_expand(t_lexer *lexer, char *val, char quote)
{
	if (!ft_strchr(lexer->line + lexer->i, quote))
		return (free(val), ft_genl_err("Unclosed quote."), NULL);
	while (lexer->c != '\0' && lexer->c != quote)
	{
		if (lexer->c == '$' && quote == '\"')
		{
			lexer_advance(lexer);
			if (lexer->c == '?')
			{
				val = ft_strjoin_char(val, g_gob.ex_status + '0');
				lexer_advance(lexer);
				continue ;
			}
			val = ft_strjoin(val, get_env_val(lexer));
			continue ;
		}
		val = ft_strjoin_char(val, lexer->c);
		lexer_advance(lexer);
	}
	return (val);
}

char	*c_expand(t_lexer *lexer, char *val)
{
	while (lexer->c != '\0' && ft_isprint(lexer->c))
	{
		if (lexer->c == '$')
		{
			lexer_advance(lexer);
			if (lexer->c == '?')
			{
				val = ft_strjoin_char(val, g_gob.ex_status + '0');
				lexer_advance(lexer);
				continue ;
			}
			if (lexer->c == '\0' || !ft_isalnum(lexer->c)) {
                val = ft_strjoin_char(val, '$');
                continue;
            }
			val = ft_strjoin(val, get_env_val(lexer));
			continue ;
		}
		val = ft_strjoin_char(val, lexer->c);
		lexer_advance(lexer);
	}
	return (val);
}