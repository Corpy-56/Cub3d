/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:10:23 by agouin            #+#    #+#             */
/*   Updated: 2026/01/23 16:15:54 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_delta_dist(t_raycast *cast, t_player *player)
{
	if (cast->ray_dir_x == 0)
		cast->delta_dist_x = 1e30;
	else
		cast->delta_dist_x = fabs(1 / cast->ray_dir_x);
	if (cast->ray_dir_y == 0)
		cast->delta_dist_y = 1e30;
	else
		cast->delta_dist_y = fabs(1 / cast->ray_dir_y);
	if (cast->ray_dir_x < 0)
	{
		cast->step_x = -1;
		cast->side_dist_x = (player->pos_col - cast->map_x)
			* cast->delta_dist_x;
	}
	else
	{
		cast->step_x = 1;
		cast->side_dist_x = (cast->map_x + 1.0 - player->pos_col)
			* cast->delta_dist_x;
	}
	return ;
}

void	radius_calcul(t_raycast *cast, t_direction *dir, t_player *player)
{
	cast->ray_dir_x = dir->dir_x + dir->plan_x * cast->camera;
	cast->ray_dir_y = dir->dir_y + dir->plan_y * cast->camera;
	calcul_delta_dist(cast, player);
	if (cast->ray_dir_y < 0)
	{
		cast->step_y = -1;
		cast->side_dist_y = (player->pos_row - cast->map_y)
			* cast->delta_dist_y;
	}
	else
	{
		cast->step_y = 1;
		cast->side_dist_y = (cast->map_y + 1.0 - player->pos_row)
			* cast->delta_dist_y;
	}
	return ;
}

void	wall_height_calcul(t_raycast *cast, t_mlx *screen)
{
	cast->line_height = (int)(screen->screen_size_height
			/ cast->wall_distance);
	cast->draw_start = -cast->line_height
		/ 2 + screen->screen_size_height / 2;
	if (cast->draw_start < 0)
		cast->draw_start = 0;
	cast->draw_end = cast->line_height
		/ 2 + screen->screen_size_height / 2;
	if (cast->draw_end >= screen->screen_size_height)
		cast->draw_end = screen->screen_size_height -1;
	return ;
}

void	ft_calcul(t_game *game, t_texture *tex, t_raycast *cast)
{
	if (cast->side == 0)
		tex->wall_t = game->player.pos_row
			+ cast->wall_distance * cast->ray_dir_y;
	else
		tex->wall_t = game->player.pos_col
			+ cast->wall_distance * cast->ray_dir_x;
	tex->wall_t -= floor(tex->wall_t);
	game->tex.tex_x = (int)(game->tex.wall_t * 64);
	wall_height_calcul(cast, &game->screen);
}

void	raycast(t_game *game, t_raycast *cast)
{
	int	i;

	ft_init_ray(cast, &game->mini);
	i = 0;
	while (i < game->screen.screen_size_width)
	{
		cast->hit = 0;
		cast->map_x = (int)game->player.pos_col;
		cast->map_y = (int)game->player.pos_row;
		cast->camera = 2.0 * i / (double)game->screen.screen_size_width - 1.0;
		radius_calcul(cast, &game->dir, &game->player);
		hit_wall_boucle(cast, game);
		if (cast->side == 0)
			cast->wall_distance = cast->side_dist_x
				- cast->delta_dist_x;
		else
			cast->wall_distance = cast->side_dist_y
				- cast->delta_dist_y;
		if (cast->wall_distance <= 0.0001)
			cast->wall_distance = 0.0001;
		ft_calcul(game, &game->tex, cast);
		draw_wall_column(cast, &game->screen, i, game);
		i++;
	}
	draw_mini_map(&game->screen, &game->player, game);
}
