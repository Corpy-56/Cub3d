/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:58:43 by skuor             #+#    #+#             */
/*   Updated: 2026/01/19 18:22:03 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_direction *dir, t_player *player)
{
	//printf("Player pos: (%f, %f)\n", player->pos_col, player->pos_row);
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
		dir->dir_y = 1.0;
		dir->plan_x = -0.66;
	}
	if (player->spawn_dir == 'E')
	{
		dir->dir_x = 1.0;
		dir->plan_y = 0.66;
	}
	if (player->spawn_dir == 'S')
	{
		dir->dir_y = -1.0;
		dir->plan_x = 0.66;
	}
	if (player->spawn_dir == 'W')
	{
		dir->dir_x = -1.0;
		dir->plan_y = -0.66;
	}
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
	mini->start_x = 20;
	mini->end_x = 220;
	mini->start_y = 20;
	mini->end_y = 220;
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
