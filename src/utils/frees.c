/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 04:50:54 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/28 06:24:59 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_command(t_parser *parser)
{
	t_command	*tmp;
	t_command	*next;
	int			i;

	tmp = parser->command;
	if (!tmp)
		return ;
	while (tmp)
	{
		next = tmp->next;
		i = ft_tabsize(tmp->items);
		while (i--)
			free(tmp->items[i]);
		free(tmp->items);
		free(tmp);
		tmp = next;
	}
	free(tmp);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}

void	dp_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
