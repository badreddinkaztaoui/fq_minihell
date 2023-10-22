/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:23:16 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/10/22 15:36:09 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer *init_lexer(char *line)
{
    t_lexer *lexer;

    lexer = malloc(sizeof(t_lexer));
    if (!lexer)
        return (NULL);
    lexer->line = line;
    lexer->line_len = ft_strlen(line);
    lexer->c = line[lexer->i];
    lexer->i = 0;
    return (lexer);
}

void lexer_advance(t_lexer *lexer)
{
    if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->line))
    {
        lexer->i++;
        lexer->c = lexer->line[lexer->i];
    }
}

t_token *lexer_advance_with(t_token *token, t_lexer *lexer)
{
    lexer_advance(lexer);
    return (token);
}

t_token  *lexer_get_next_token(char *src, char **env)
{
  t_lexer *lexer;

  lexer = init_lexer(src);
  while (lexer->c != '\0')
  {
    if (ft_iswp(lexer->c))
      lexer_advance(lexer);
    if (ft_isalpha(lexer->c))
      return (lexer_collect_cmd(lexer));
    if (lexer->c == '|')
      return (lexer_advance_with(init_token(ft_strdup("|"), PIPE), lexer));
    if (lexer->c == '<')
      return (lexer_advance_with(init_token(ft_strdup("<"), REDIR_IN), lexer));
    if (lexer->c == '>')
      return (lexer_advance_with(init_token(ft_strdup(">"), REDIR_OUT), lexer));
    if (lexer->c =='\'')
      return (lexer_advance_with(lexer_collect_squote(lexer), lexer));
    if (lexer->c == '\"')
      return (lexer_advance_with(lexer_collect_dquote(lexer, env), lexer));
    if (lexer->c == '<')
      return (lexer_collect_larrow(lexer));
    if (lexer->c == '>')
      return (lexer_collect_rarrow(lexer));
  }
  return (init_token(ft_strdup("EOF"), END));
}
