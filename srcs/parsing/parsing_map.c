/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:11:02 by skuor             #+#    #+#             */
/*   Updated: 2026/01/05 15:56:19 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_map(char *line, int fd, t_map *map)
{
	char	*map_tmp;

	if (!line)
		return (1);
	map_tmp = ft_strdup("");
	if (!map_tmp)
		return (1);
	while (line)
	{
		map_tmp = ft_strjoin_free(map_tmp, line);
		if (!map_tmp)
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	map->big_map = ft_split(map_tmp, '\n');
	free(map_tmp);
	if (!map->big_map || !map->big_map[0])
		return (free_doublechar(map->big_map), 1);
	return (0);
}
