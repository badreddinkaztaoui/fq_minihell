/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:36:15 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/11 04:22:14 by bkaztaou         ###   ########.fr       */
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
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/* ===== Color ===== */
# define LIGHT_BLUE "\x1B[1;34m"
# define RESET "\x1B[0m"
# define R_FILE "/dev/random"
# define R_FILE_SIZE 4

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

typedef struct s_token
{
	char			*value;
	t_types			type;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	char	*line;
	size_t	line_len;
	char	c;
	size_t	i;
}	t_lexer;

typedef struct s_command
{
	int					in_fd;
	int					out_fd;
	int					index;
	char				**items;
	struct s_command	*next;
}	t_command;

typedef struct s_parser
{
	t_command	*command;
	t_token		*next_token;
	t_token		*prev_token;
}	t_parser;

typedef struct s_minishell
{
	char	*line;
	t_lexer	*lexer;
	char	**env;
}	t_minishell;

/* ===== Prototypes ===== */

// Minishell
void		minishell_loop(t_minishell *minishell,
				t_parser *parser, char **env);
void		minishell_exit(t_minishell *minishell);
// Tokens
t_token		*init_token(char *value, t_types type);
t_token		*clone_token(t_token *token);
int			is_valid_pipe_pos(t_parser *parser);
int			is_valid_end_cmd(t_parser *parser);
// Lexer
t_lexer		*init_lexer(char *line);
void		lexer_advance(t_lexer *lexer);
t_token		*lexer_advance_with(t_token *token, t_lexer *lexer);
char		*lexer_get_env_value(t_lexer *lexer, char **env);
t_token		*lexer_collect_cmd(t_lexer *lexer, char **env);
t_token		*lexer_collect_squote(t_lexer *lexer);
t_token		*lexer_collect_dquote(t_lexer *lexer, char **env);
t_token		*lexer_collect_rarrow(t_lexer *lexer);
t_token		*lexer_collect_larrow(t_lexer *lexer);
// Tokenizer
t_token		*lexer_get_next_token(t_lexer *lexer, char **env);
// Parser
t_command	*init_command(void);
void		init_parser(t_parser *parser);
void		parse(t_lexer *lexer, char **env, t_parser *parser);
void		ft_heredoc(char *del, t_command *cmd, char **env);
// Utils
void		*ft_realloc(void *ptr, size_t size);
// Free
void		free_token(t_token *token);
void		free_command(t_parser *parser);
// Testers
void		print_tokens(t_lexer *lexer, char **env);
void		print_command(t_command *command);
// Exiters
void		ft_unexpected_token(char *token);

#endif