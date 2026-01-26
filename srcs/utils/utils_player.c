/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:18:15 by skuor             #+#    #+#             */
/*   Updated: 2026/01/26 14:39:48 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_parse(t_game *game, t_config *c)
{
	int	i;

	i = 0;
	if (!c->no_path || !c->ea_path || !c->so_path || !c->we_path)
		return (1);
	if (game->floor.r == -1 || game->ceiling.r == -1)
		return (1);
	if (!game->map.big_map)
		return (1);
	return (0);
}

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

	next_tile = game->map.big_map[(int)(new_y + OFFSET)][(int)new_x];
	if (next_tile == '1')
		return (true);
	next_tile = game->map.big_map[(int)(new_y - OFFSET)][(int)new_x];
	if (next_tile == '1')
		return (true);
	next_tile = game->map.big_map[(int)new_y][(int)(new_x + OFFSET)];
	if (next_tile == '1')
		return (true);
	next_tile = game->map.big_map[(int)new_y][(int)(new_x - OFFSET)];
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
