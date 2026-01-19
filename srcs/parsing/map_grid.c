/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:35:04 by skuor             #+#    #+#             */
/*   Updated: 2026/01/19 15:04:04 by agouin           ###   ########.fr       */
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
			return (free_rows(grid, y), NULL);
		while (x < cols)
		{
			grid[y][x] = ' ';
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
		if (line[len - 1] == '\n')
			len -= 1;
		x = 0;
		while (x < (ft_min(len, map->cols)))
		{
			grid[y][x] = line[x];
			x++;
		}
		y++;
	}
	return (grid);
}

char	**add_border(char **grid, int rows, int cols)
{
	char	**border;
	int		new_rows;
	int		new_cols;
	int		x;
	int		y;

	new_rows = rows + 2;
	new_cols = cols + 2;
	border = alloc_grid(new_rows, new_cols);
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			border[y + 1][x + 1] = grid[y][x];
			x++;
		}
		y++;
	}
	return (border);
}

char	**normalize_map(t_map *map)
{
	char	**grid;
	char	**border;

	map_size(map);
	grid = alloc_grid(map->rows, map->cols);
	map_in_grid(grid, map);
	border = add_border(grid, map->rows, map->cols);
	free_doublechar(grid);
	return (border);
}

bool	validate_map(t_game *game)
{
	if (!check_closed_map(game))
		return (false);
	if (check_elements(game->map.big_map))
		return (false);
	fill_space(game->map.big_map);
	ft_printf(GREEN"Valid map !\n"DEFAULT);
	return (true);
}
