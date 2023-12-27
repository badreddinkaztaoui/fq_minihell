/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:42:41 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/27 21:27:53 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gob	g_gob;

void	minishell_loop(t_minishell *minishell, t_parser *parser)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		minishell->line = readline(LIGHT_BLUE "👾 minishell $ " RESET);
		if (!minishell->line)
			ctrl_d();
		add_history(minishell->line);
		minishell->lexer = init_lexer(minishell->line);
		if (parse(minishell->lexer, parser))
		{
			minishell_exit(minishell);
			continue ;
		}
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
	if (!env[0])
	{
		ft_putendl_fd("minishell: env is empty", 2);
		exit(1);
	}
	init_envs(env);
	g_gob.s_env = clone_env();
	minishell_loop(&minishell, &parser);
	clear_history();
	minishell_exit(&minishell);
	return (0);
}
