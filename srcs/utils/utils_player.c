/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:18:15 by skuor             #+#    #+#             */
/*   Updated: 2026/01/22 13:59:12 by skuor            ###   ########.fr       */
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

void	calc_delta(t_game *game)
{
	struct timeval	time;
	double			now;

	if (gettimeofday(&time, NULL) == -1)
		return ;
	now = time.tv_sec + time.tv_usec / 1000000.0;
	if (game->time.last == 0)
	{
		game->time.last = now;
		game->time.delta = 0;
		return ;
	}
	game->time.delta = now - game->time.last;
	if (game->time.delta > 0.5)
		game->time.delta = 0.5;
	game->time.last = now;
}
