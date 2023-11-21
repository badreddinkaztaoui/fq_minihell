/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:36:15 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/11/22 00:10:56 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/* ===== Color ===== */
#define LIGHT_BLUE "\x1B[1;34m"
#define RESET "\x1B[0m"

/* ===== Prototypes ===== */

typedef enum s_types
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	END,
}	t_types;

typedef struct s_lexer
{
	char	*line;
	size_t	line_len;
	char	c;
	size_t	i;
}	t_lexer;

typedef struct s_token
{
	char			*value;
	t_types			type;
	struct s_token	*next;
}	t_token;

typedef struct s_parser
{
	t_token			*token;
	struct s_parser	*curr;
	struct s_parser	*next;
}	t_parser;

typedef struct s_minishell
{
	char	*line;
	t_lexer	*lexer;
	char	**env;
}	t_minishell;

/* ===== Prototypes ===== */

// Minishell
void    minishell_loop(t_minishell *minishell, char **env);
void    minishell_exit(t_minishell *minishell);
// Tokens
t_token *init_token(char *value, t_types type);
void	print_tokens(t_lexer *lexer, char **env);
// Lexer
t_lexer *init_lexer(char *line);
void    lexer_advance(t_lexer *lexer);
t_token *lexer_advance_with(t_token *token, t_lexer *lexer);
char	*lexer_get_env_value(t_lexer *lexer, char **env);
t_token *lexer_collect_cmd(t_lexer *lexer, char **env);
t_token	*lexer_collect_squote(t_lexer *lexer);
t_token	*lexer_collect_dquote(t_lexer *lexer, char **env);
t_token	*lexer_collect_rarrow(t_lexer *lexer);
t_token	*lexer_collect_larrow(t_lexer *lexer);
// Tokenizer
t_token	*lexer_get_next_token(t_lexer *lexer, char **env);
// Utils
char	*ft_strjoin_char(char *s1, char c);

#endif