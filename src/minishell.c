/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:42:41 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/11/22 00:15:22 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell_loop(t_minishell *minishell, char **env)
{
	minishell->env = env;
	while (1)
	{
		minishell->line = readline(LIGHT_BLUE "👾 minishell $ " RESET);
		add_history(minishell->line);
		minishell->lexer = init_lexer(minishell->line);
		if (ft_strncmp(minishell->line, "exit", 4) == 0)
			break ;
		print_tokens(minishell->lexer, env);
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
	t_minishell minishell;

	(void)argc;
	(void)argv;
	minishell_loop(&minishell, env);
	clear_history();
	minishell_exit(&minishell);
	return (0);
}