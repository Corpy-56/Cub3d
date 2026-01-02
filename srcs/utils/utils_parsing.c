/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:35:03 by skuor             #+#    #+#             */
/*   Updated: 2026/01/02 17:35:21 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	match_id(const char *line, int i, const char *id)
{
	if (line[i] == id[0] && line[i + 1] == id[1])
		if (is_whitespace(line[i + 2]))
			return (1);
	return (0); 
}

int	extract_path(const char *line, int start, char **path, int *after)
{
	int i;
	
	if (!line || !after || !path)
		return (0);
	*path = NULL;
	start = skip_ws(line, start);
	if (line[start] == '\0' || line[start] == '\n')
	{
		ft_printf("error path");
		return (0);
	}
	i = start;
	while (!is_whitespace(line[i]) && line[i] != '\n' && line[i] != '\0')
		i++;
	*path = ft_substr(line, start, i - start);
	if (*path == NULL)
		return (0);
	*after = i;
	return (1);
}