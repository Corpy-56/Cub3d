/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:07:23 by skuor             #+#    #+#             */
/*   Updated: 2026/01/13 16:14:12 by skuor            ###   ########.fr       */
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
	else if (f->map[y][x] == ' ')
		f->map[y][x] = '.';
	flood_fill(f, y + 1, x);
	flood_fill(f, y - 1, x);
	flood_fill(f, y, x + 1);
	flood_fill(f, y, x - 1);
}

// void	flood_fill(char **map, int y, int x, int rows, int cols)
// {
// 	if (x < 0 || y < 0 || x >= cols || y >= rows)
// 		return ;
// 	if (map[y][x] == '1' || map[y][x] == '.')
// 		return ;
// 	else if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'S' || map[y][x] == 'W')
// 		return ;
// 	else if (map[y][x] == ' ')
// 		map[y][x] = '.';
// 	flood_fill(map, y + 1, x, rows, cols);
// 	flood_fill(map, y - 1, x, rows, cols);
// 	flood_fill(map, y, x + 1, rows, cols);
// 	flood_fill(map, y, x - 1, rows, cols);
// }

bool	check_closed_map(t_game *game)
{
	t_flood	flood;

	init_flood(&flood, &game->map);
	flood.map = normalize_map(&game->map);
	if (!flood.map)
		return (error_msg("Map could not be duplicate"), false);
	flood_fill(&flood, 0, 0);
	ft_print_map(flood.map);
	if (flood.open == true)
		return (error_msg("Map is open"), false);
	return (true);
}

