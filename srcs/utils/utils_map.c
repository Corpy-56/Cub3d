/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:14:41 by skuor             #+#    #+#             */
/*   Updated: 2026/01/12 17:39:37 by skuor            ###   ########.fr       */
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
		if (len > max)
			max = len;
		i++;
	}
	map->rows = i;
	map->cols = max;
	ft_printf("rows : %d\ncols : %d\n", map->rows, map->cols);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
