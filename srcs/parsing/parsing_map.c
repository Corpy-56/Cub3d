/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:11:02 by skuor             #+#    #+#             */
/*   Updated: 2026/01/06 11:42:25 by skuor            ###   ########.fr       */
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
		return (free(line), 1);
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

bool	is_map_line(const char *line)
{
	int		i;
	bool	found_char;

	found_char = false;
	if (!line)
		return (false);
	i = skip_ws(line, 0);
	if (line[i] == '\n' || line[i] == '\0')
		return (false);
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'W' && line[i] != 'E' && line[i] != 'S' && line[i] != ' ')
			return (ft_printf("Unknown character in map\n"), false);
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'W' || line[i] == 'E' || line[i] == 'S')
		{
			ft_printf("Found %c\n", line[i]);
			found_char = true;
		}
		i++;
	}
	return (found_char);
}