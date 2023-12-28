/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:36:15 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 06:14:57 by bkaztaou         ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

// COLORS
# define LIGHT_BLUE "\x1B[1;34m"
# define RESET "\x1B[0m"
# define R_FILE "/dev/random"
# define R_FILE_SIZE 4

// Global Variables
typedef struct s_gob
{
	int		ex_status;
	int		heredoc_count;
	char	**env;
	char	**s_env;
}	t_gob;

typedef enum s_types
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	SQUOTE,
	DQUOTE,
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
	int					fds[2];
	char				**items;
	int					index;
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
void		minishell_loop(t_minishell *minishell, t_parser *parser);
void		minishell_exit(t_minishell *minishell);
// Tokens
t_token		*init_token(char *value, t_types type);
t_token		*clone_token(t_token *token);
void		init_envs(char **env);
// Lexer
t_lexer		*init_lexer(char *line);
void		lexer_advance(t_lexer *lexer);
t_token		*lexer_advance_with(t_token *token, t_lexer *lexer);
char		*get_env_val(t_lexer *lexer);
char		*lexer_collect_escape(t_lexer *lexer);
char		*lexer_collect_dollar(t_lexer *lexer);
char		*lexer_collect_squote(t_lexer *lexer);
char		*lexer_collect_dquote(t_lexer *lexer);
t_token		*lexer_collect_rarrow(t_lexer *lexer);
t_token		*lexer_collect_larrow(t_lexer *lexer);
// Tokenizer
t_token		*lexer_get_next_token(t_lexer *lexer);
// Expands
char		*q_expand(t_lexer *lexer, char *val, char quote);
// Parser
t_command	*init_command(void);
void		init_parser(t_parser *parser);
int			parse(t_lexer *lexer, t_parser *parser);
char		*ft_genname(void);
int			heredoc(t_token *del, t_command **cmd);
void		ft_heredoc(t_token *del, char *filename);
int			handle_redirection(t_command **cmd, t_parser *pars);
// PARSING CHECKERS
int			is_iofiles(t_token *token);
int			is_redirection(t_token *token);
int			is_not_cmd(t_token *token);
int			can_add_cmd(t_parser *parser);
int			is_valid_cmd(t_parser *parser);
// Execution
void		execution(t_command *cmd);
int			is_builtin(char *command);
void		ft_builtins(t_command *cmd);
void		run_cmds(t_command *cmd);
void		execute_cmds(t_command *cmd, t_command *tmp, int size);
void		execute_one_cmd(t_command *cmd);
void		execute_pipes(t_command *cmd, t_command *tmp);
void		execute_last_cmd(t_command *cmd, t_command *tmp);
void		ft_close_files(t_command *cmd, t_command *tmp);
void		ft_close_all(t_command *cmd, t_command *tmp);
void		ft_setenv(char *item);
void		ft_export_nxt(t_command *cmd);

// Builtins
void		ft_echo(t_command *cmd);
void		ft_cd(t_command *cmd);
void		ft_pwd(t_command *cmd);
int			ft_export(t_command *cmd);
void		ft_unset(t_command *cmd);
void		ft_env(t_command *cmd);
void		ft_exit(t_command *cmd);
// SIGNALS
void		ctrl_(int num);
void		ctrl_c(int num);
void		ctrl_d(void);
// Utils
void		*ft_realloc(void *ptr, size_t size);
int			ft_listsize(t_command *lst);
int			ft_tabsize(char **tab);
void		sort_by_key(char **envp);
void		export_print(void);
char		*ft_getkey(char *command);
int			is_valid_key(char *command);
int			export_err(t_command *cmd, char *key, int i);
int			is_valid_key(char *command);
char		**ft_tabjoin(char **envp, char *env);
int			is_keyexist(char *key, char **envp);
char		*ft_getenv(char *key, char *val, int has_equal);
char		*ft_geteval(char *key);
char		**clone_env(void);
// Free
void		free_token(t_token *token);
void		free_command(t_parser *parser);
void		dp_free(char **str);
// Testers
void		print_tokens(t_lexer *lexer);
void		print_command(t_command *command);
// Exiters
void		ft_unexpected_token(char *token);
void		ft_genl_err(char *token);
void		ft_nofile(char *token);
void		ft_cmd_not_found(char *command);
void		throw_error(t_command *cmd);

extern t_gob	g_gob;

#endif
