/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 09:33:59 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/12/22 23:17:42 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*clone_token(t_token *token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = token->type;
	new_token->value = malloc(sizeof(char) * (ft_strlen(token->value) + 1));
	if (!new_token->value)
		return (NULL);
	ft_strlcpy(new_token->value, token->value, ft_strlen(token->value) + 1);
	return (new_token);
}
