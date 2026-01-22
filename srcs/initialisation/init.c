/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:58:43 by skuor             #+#    #+#             */
/*   Updated: 2026/01/22 16:18:54 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dir(t_direction *dir)
{
	dir->turn_left = false;
	dir->turn_right = false;
	dir->forward = false;
	dir->backward = false;
	dir->strafe_r = false;
	dir->strafe_l = false;
	dir->plane_len = tan(FOV / 2);
	dir->rot_speed = 0.05;
	dir->move_speed = 0.05;
}

void	init_tex(t_tex *tex)
{
	tex->i = 0;
	tex->j = 0;
	tex->start = 0;
	tex->path = NULL;
	tex->fd = 0;
}

void	init_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

void	init_config(t_config *config, t_game *game)
{
	init_color(&game->floor);
	init_color(&game->ceiling);
	config->no_path = NULL;
	config->so_path = NULL;
	config->we_path = NULL;
	config->ea_path = NULL;
}

void	init_parse_map(t_parse_map *p_map)
{
	p_map->map_tmp = ft_strdup("");
	p_map->started = false;
	p_map->end = false;
	p_map->rows = 0;
}
