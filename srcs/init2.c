/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:58:43 by skuor             #+#    #+#             */
/*   Updated: 2026/01/22 13:44:53 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	init_config(&game->config, game);
	init_dir(&game->dir);
	init_mouse(&game->mouse);
	init_time(&game->time);
	// init_map(&game->dir, &game->map);
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
}

void	init_time(t_time *time)
{
	time->delta = 0;
	time->last = 0;
}
