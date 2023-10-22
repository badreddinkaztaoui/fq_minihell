/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <bkaztaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:42:41 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/10/22 15:46:26 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    minishell_loop(t_minishell *minishell, char **env)
{
    t_token *token;
    minishell->env = env;
    while (1)
    {
        minishell->line = readline(LIGHT_BLUE "👾 minishell $ " RESET);
        if (ft_strncmp(minishell->line, "exit", 4) == 0)
            exit(0);
    }
}

void    minishell_exit(t_minishell *minishell)
{
    free(minishell->line);
}

int main(int argc, char **argv, char **env)
{
    t_minishell minishell;

    (void)argc;
    (void)argv;
    minishell_loop(&minishell, env);
    return (0);
}