/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:58:43 by skuor             #+#    #+#             */
/*   Updated: 2026/01/14 17:31:23 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config(t_config *config)
{
	config->no_path = NULL;
	config->so_path = NULL;
	config->we_path = NULL;
	config->ea_path = NULL;
	config->floor_r = -1;
	config->floor_g = -1;
	config->floor_b = -1;
	config->ceiling_r = -1;
	config->ceiling_g = -1;
	config->ceiling_b = -1;
	config->dir.pos_x = 7.0;//peut etre changer en fonction de la map
	config->dir.pos_y = 3.5;
	config->dir.dir_x = -1.0;//il faut changer ca en fonction de la map cest ou il regarde
	config->dir.dir_y = 0.0;
	config->dir.plan_x = 0.0;
	config->dir.plan_y = 0.66;
	//config->map = NULL;
	config->map.map_height = 5;//a changer 
	config->map.map_width = 9;// achanger
	config->map.player_x = 7;
	config->map.player_y = 1;
}

void	init_tex(t_tex *tex)
{
	tex->i = 0;
	tex->j = 0;
	tex->start = 0;
	tex->path = NULL;
	tex->fd = 0;
}

void	ft_init_ray(t_config *config)
{
	config->cast.camera = 0.0;
	config->cast.ray_dir_x = 0.0;
	config->cast.ray_dir_y = 0.0;
	config->cast.side_dist_x = 0.0;
	config->cast.side_dist_y = 0.0;
	config->cast.delta_dist_x = 0.0;
	config->cast.delta_dist_y = 0.0;
	config->cast.wall_distance = 0.0;
	config->cast.step_x = 0;
	config->cast.step_y = 0;
	config->cast.draw_start = 0;
	config->cast.draw_end = 0;
	config->cast.hit = 0;
	config->cast.side = 0;
	config->cast.map_x = 0;
	config->cast.line_height = 0;
	config->cast.map_y = 0;
	config->mini.start_x = 10;
	config->mini.end_x = 310;
	config->mini.start_y = 10;
	config->mini.end_y = 310;
}
