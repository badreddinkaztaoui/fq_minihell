/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 09:33:59 by bkaztaou          #+#    #+#             */
/*   Updated: 2023/11/22 00:04:58 by bkaztaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *init_token(char *value, t_types type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->value = value;
    token->type = type;
    token->next = NULL;
    return (token);
}