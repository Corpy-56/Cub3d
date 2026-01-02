/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:52:37 by skuor             #+#    #+#             */
/*   Updated: 2026/01/02 17:35:26 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_ws(const char *line, int i)
{
	while (is_whitespace(line[i]))
		i++;
	return (i);
}

bool	ws_eol(const char *line, int pos)
{
	pos = skip_ws(line, pos);
	if (line[pos] != '\n' && line[pos] != '\0')
		return (false);
	return (true);
}

bool	is_whitespace(char ws)
{
	if (ws == ' ' || ws == '\t')
		return (true);
	return (false);
}
bool	no_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (true);
		i++;
	}
	return (false);
}