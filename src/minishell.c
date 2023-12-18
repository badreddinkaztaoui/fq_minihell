/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:42:41 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/18 04:57:26 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell_loop(t_minishell *minishell, t_parser *parser, char **env)
{
	minishell->env = env;
	while (1)
	{
		minishell->line = readline(LIGHT_BLUE "👾 minishell $ " RESET);
		add_history(minishell->line);
		minishell->lexer = init_lexer(minishell->line);
		if (ft_strncmp(minishell->line, "exit", 4) == 0)
			break ;
		parse(minishell->lexer, minishell->env, parser);
		print_command(parser->command);
		free_command(parser);
		minishell_exit(minishell);
	}
}

void	minishell_exit(t_minishell *minishell)
{
	free(minishell->line);
	free(minishell->lexer);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	t_parser	parser;

	(void)argc;
	(void)argv;
	g_gob.ex_status = 0;
	minishell_loop(&minishell, &parser, env);
	clear_history();
	minishell_exit(&minishell);
	return (0);
}
