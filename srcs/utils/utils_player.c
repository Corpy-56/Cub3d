/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:18:15 by skuor             #+#    #+#             */
/*   Updated: 2026/01/22 12:17:00 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > (2 * PI))
		angle -= 2 * PI;
	return (angle);
}

void	calc_dir_plan(t_direction *dir)
{
	dir->dir_x = cos(dir->angle);
	dir->dir_y = sin(dir->angle);
	dir->plan_x = (-dir->dir_y) * dir->plane_len;
	dir->plan_y = dir->dir_x * dir->plane_len;
}

bool	check_walls(t_game *game, double new_x, double new_y)
{
	char	next_tile;
	int		map_x;
	int		map_y;

	map_x = new_x;
	map_y = new_y;
	next_tile = game->map.big_map[map_y][map_x];
	if (next_tile == '1')
		return (true);
	return (false);
}

