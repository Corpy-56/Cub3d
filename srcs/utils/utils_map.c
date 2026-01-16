/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:14:41 by skuor             #+#    #+#             */
/*   Updated: 2026/01/14 17:45:55 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_size(t_map *map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	if (!map->big_map)
		return ;
	while (map->big_map[i])
	{
		len = ft_strlen(map->big_map[i]);
		if (len > 0)
		{
			if (map->big_map[i][len - 1] == '\n')
				len -= 1;
		}
		if (len > max)
			max = len;
		i++;
	}
	map->rows = i;
	map->cols = max;
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	free_rows(char **grid, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(grid[j]);
		j++;
	}
	free(grid);
}

int	check_size_map(char *line, t_parse_map *p)
{
	int	len;
	int	max;

	max = 0;
	len = ft_strlen(line);
	if (len > 0)
	{
		if (line[len - 1] == '\n')
			len -= 1;
	}
	if (p->rows + 1 > 250 || len > 250)
		return (error_msg("Map is too big"), 1);
	return (0);
}
