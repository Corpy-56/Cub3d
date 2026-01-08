/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:58:43 by skuor             #+#    #+#             */
/*   Updated: 2026/01/08 15:42:46 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map)
{
	map->big_map = NULL;
	map->map_height = 0;
	map->map_width = 0;
	map->player_x = -1;
	map->player_y = -1;
}

void	init_tex(t_tex *tex)
{
	tex->i = 0;
	tex->j = 0;
	tex->start = 0;
	tex->path = NULL;
	tex->fd = 0;
}

void	init_config(t_config *config)
{
	init_color(&config->floor);
	init_color(&config->ceiling);
	config->no_path = NULL;
	config->so_path = NULL;
	config->we_path = NULL;
	config->ea_path = NULL;
}

void	init_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

void	init_game(t_game *game)
{
	init_config(&game->config);
	init_map(&game->map);
}
