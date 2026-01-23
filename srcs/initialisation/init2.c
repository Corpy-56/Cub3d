/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:58:43 by skuor             #+#    #+#             */
/*   Updated: 2026/01/23 11:24:38 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	init_config(&game->config, game);
	init_dir(&game->dir);
	init_mouse(&game->mouse);
	init_time(&game->time);
}

static void	init_map2(t_direction *dir, t_player *player)
{
	if (player->spawn_dir == 'S')
	{
		dir->dir_y = 1.0;
		dir->plan_x = -0.66;
	}
	if (player->spawn_dir == 'W')
	{
		dir->dir_x = -1.0;
		dir->plan_y = -0.66;
	}
}

int	init_map(t_direction *dir, t_player *player)
{
	if (player->spawn_dir == 'N' || player->spawn_dir == 'S')
	{
		dir->dir_x = 0.0;
		dir->plan_y = 0.0;
	}
	if (player->spawn_dir == 'E' || player->spawn_dir == 'W')
	{
		dir->dir_y = 0.0;
		dir->plan_x = 0.0;
	}
	if (player->spawn_dir == 'N')
	{
		dir->dir_y = -1.0;
		dir->plan_x = 0.66;
	}
	if (player->spawn_dir == 'E')
	{
		dir->dir_x = 1.0;
		dir->plan_y = 0.66;
	}
	init_map2(dir, player);
	return (1);
}

void	init_border(t_ext *ext, int rows, int cols)
{
	ext->new_rows = rows + 2;
	ext->new_cols = cols + 2;
	ext->x = 0;
	ext->y = 0;
}

void	init_flood(t_flood *flood, t_map *map)
{
	flood->rows = map->rows + 2;
	flood->cols = map->cols + 2;
	flood->open = false;
}

void	init_mouse(t_mouse *mouse)
{
	mouse->init = false;
	mouse->sens = 0.01;
	mouse->lock = false;
	mouse->last_x = 0;
	mouse->x = 0;
	mouse->y = 0;
}

void	init_time(t_time *time)
{
	time->delta = 0;
	time->last = 0;
}
