/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:28:30 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/13 02:53:30 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redirection(t_command **cmd, t_parser *pars, char **env)
{
	if (pars->prev_token->type == HEREDOC)
		heredoc(pars->next_token->value, cmd, env);
}
