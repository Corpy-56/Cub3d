/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:07:23 by skuor             #+#    #+#             */
/*   Updated: 2026/01/26 16:46:07 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(t_flood *f, int y, int x)
{
	if (x < 0 || y < 0 || x >= f->cols || y >= f->rows)
		return ;
	if (f->map[y][x] == '1' || f->map[y][x] == '.')
		return ;
	else if (f->map[y][x] == '0' || f->map[y][x] == 'N'
		|| f->map[y][x] == 'E' || f->map[y][x] == 'S' || f->map[y][x] == 'W')
	{
		f->open = true;
		return ;
	}
	else if (f->map[y][x] == ' ' || f->map[y][x] == '	')
		f->map[y][x] = '.';
	flood_fill(f, y + 1, x);
	flood_fill(f, y - 1, x);
	flood_fill(f, y, x + 1);
	flood_fill(f, y, x - 1);
}

bool	voisins(char **map, int i, int j)
{
	if (ft_strchr("0NEWS", map[i + 1][j]))
		return (true);
	else if (ft_strchr("0NEWS", map[i - 1][j]))
		return (true);
	else if (ft_strchr("0NEWS", map[i][j + 1]))
		return (true);
	else if (ft_strchr("0NEWS", map[i][j - 1]))
		return (true);
	return (false);
}

bool	space_in_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				if (voisins(map, i, j))
					return (true);
			j++;
		}
		i++;
	}
	return (false);
}

bool	check_closed_map(t_game *game)
{
	t_flood	flood;

	flood.map = normalize_map(&game->map);
	if (!flood.map)
		return (error_msg("Map could not be duplicate"), false);
	init_flood(&flood, &game->map);
	flood_fill(&flood, 0, 0);
	if (flood.open == true)
	{
		free_doublechar(flood.map);
		return (error_msg("Map is open"), false);
	}
	if (space_in_map(flood.map))
	{
		free_doublechar(flood.map);
		return (error_msg("Space in map"), false);
	}
	free_doublechar(flood.map);
	return (true);
}
