/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:42:41 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/26 13:00:38 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gob	g_gob;

void	minishell_loop(t_minishell *minishell, t_parser *parser)
{
	while (1)
	{
		minishell->line = readline(LIGHT_BLUE "👾 minishell $ " RESET);
		add_history(minishell->line);
		minishell->lexer = init_lexer(minishell->line);
		if (parse(minishell->lexer, parser))
		{
			minishell_exit(minishell);
			continue ;
		}
		// print_command(parser->command);
		execution(parser->command);
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
	g_gob.heredoc_count = 0;
	init_envs(env);
	minishell_loop(&minishell, &parser);
	clear_history();
	minishell_exit(&minishell);
	return (0);
}
