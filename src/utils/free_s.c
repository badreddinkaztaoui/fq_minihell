/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 04:50:54 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/11/28 03:58:39 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_command(t_parser *parser)
{
	t_command	*tmp;
	t_command	*next;
	int			i;

	tmp = parser->command;
	while (tmp)
	{
		next = tmp->next;
		i = tmp->index;
		while (i--)
			free(tmp->items[i]);
		free(tmp->items);
		free(tmp);
		tmp = next;
	}
}

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}