/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:35:04 by skuor             #+#    #+#             */
/*   Updated: 2026/01/12 17:50:19 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**alloc_grid(int rows, int cols)
{
	char	**grid;
	int		x;
	int		y;

	y = 0;
	grid = malloc(sizeof(char *) * (rows + 1));
	if (!grid)
		return (NULL);
	while (y < rows)
	{
		x = 0;
		grid[y] = malloc(sizeof(char) * (cols + 1));
		if (!grid[y])
			return (NULL);
		while (x < cols)
		{
			grid[y][x] = '.'; // remplacer le '.' par un espace
			x++;
		}
		grid[y][cols] = '\0';
		y++;
	}
	grid[rows] = NULL;
	return (grid);
}

char	**map_in_grid(char **grid, t_map *map)
{
	int		x;
	int		y;
	int		len;
	char	*line;

	y = 0;
	while (y < map->rows)
	{
		line = map->big_map[y];
		len = ft_strlen(line);
		x = 0;
		while (x < (ft_min(len, map->cols) - 1))
		{
			grid[y][x] = line[x];
			x++;
		}
		y++;
	}
	return (grid);
}

char	**normalize_map(t_map *map)
{
	char	**grid;

	map_size(map);
	grid = alloc_grid(map->rows, map->cols);
	map_in_grid(grid, map);
	ft_print_map(grid);
	return (grid);
}

bool	validate_map(t_game *game)
{
	if (check_elements(game->map.big_map))
		return (false);
	ft_printf(GREEN"Valid map !\n"DEFAULT);
	return (true);
}
