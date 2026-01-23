/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:14:41 by skuor             #+#    #+#             */
/*   Updated: 2026/01/23 17:44:44 by agouin           ###   ########.fr       */
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
