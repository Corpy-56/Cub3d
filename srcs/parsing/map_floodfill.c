/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:07:23 by skuor             #+#    #+#             */
/*   Updated: 2026/01/19 14:57:25 by skuor            ###   ########.fr       */
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

void	fill_space(char **map)
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
				map[i][j] = '0';
			j++;
		}
		i++;
	}
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
	ft_print_map(flood.map); // a retirer
	free_doublechar(flood.map);
	return (true);
}
