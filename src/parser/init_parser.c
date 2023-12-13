/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 04:18:19 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/13 02:50:48 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->in_fd = 0;
	command->out_fd = 1;
	command->index = 0;
	command->items = NULL;
	command->next = NULL;
	return (command);
}

void	init_parser(t_parser *parser)
{
	parser->command = init_command();
	parser->prev_token = NULL;
	parser->next_token = NULL;
}
