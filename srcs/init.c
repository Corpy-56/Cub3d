/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:58:43 by skuor             #+#    #+#             */
/*   Updated: 2026/01/21 17:25:39 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	init_map(t_direction *dir, t_map * map)
// {
// 	dir->dir_x = -1.0;//il faut changer ca en fonction de la map cest ou il regarde
// 	dir->dir_y = 0.0;
// 	dir->plan_x = 0.0;
// 	dir->plan_y = 0.66;
// 	//map->map_height = 5;//a changer 
// 	//map->map_width = 9;// achanger
// 	map->player_x = 7;
// 	map->player_y = 1;
// }

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

void	ft_init_ray(t_raycast *cast, t_mini_map *mini)
{
	cast->camera = 0.0;
	cast->ray_dir_x = 0.0;
	cast->ray_dir_y = 0.0;
	cast->side_dist_x = 0.0;
	cast->side_dist_y = 0.0;
	cast->delta_dist_x = 0.0;
	cast->delta_dist_y = 0.0;
	cast->wall_distance = 0.0;
	cast->step_x = 0;
	cast->step_y = 0;
	cast->draw_start = 0;
	cast->draw_end = 0;
	cast->hit = 0;
	cast->side = 0;
	cast->map_x = 0;
	cast->line_height = 0;
	cast->map_y = 0;
	mini->start_x = 10;
	mini->end_x = 310;
	mini->start_y = 10;
	mini->end_y = 310;
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

void	init_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

void	init_parse_map(t_parse_map *p_map)
{
	p_map->map_tmp = ft_strdup("");
	p_map->started = false;
	p_map->end = false;
	p_map->rows = 0;
}
