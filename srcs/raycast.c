/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:10:23 by agouin            #+#    #+#             */
/*   Updated: 2026/01/22 15:03:11 by agouin           ###   ########.fr       */
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

void	hit_wall_boucle(t_raycast *cast, t_game *game)
{
	while (cast->hit == 0)
	{
		if (cast->map_x < 0 || cast->map_y < 0)
			break ;
		if (cast->map_y >= game->map.rows
			|| cast->map_x >= game->map.cols)
			break ;
		if (cast->side_dist_x < cast->side_dist_y)
		{
			cast->side_dist_x += cast->delta_dist_x;
			cast->map_x += cast->step_x;
			cast->side = 0;
		}
		else
		{
			cast->side_dist_y += cast->delta_dist_y;
			cast->map_y += cast->step_y;
			cast->side = 1;
		}
		if (game->map.big_map[cast->map_y][cast->map_x] == '1')
			cast->hit = 1;
	}
	return ;
}


void	my_mlx_pixel_put(t_mlx *screen, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= screen->screen_size_width || y >= screen->screen_size_height)
		return;
	dst = screen->addr + (y * screen->line_len + x * (screen->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_print_mini_map(t_raycast *cast, t_mlx *screen, t_mini_map *mini, int x, int y)
{
	int i;

	i = 0;
	while(y < screen->screen_size_height)
	{
		if(y >= mini->start_y && y < mini->end_y)// a voit si je mets y < mini->end_y
			i++;
		else if (y < cast->draw_start && (y <= mini->start_y || y >= mini->end_y))
			my_mlx_pixel_put(screen, x, y, 0x87CEEB);
		else if (y <= cast->draw_end && (y <= mini->start_y || y >= mini->end_y))
			my_mlx_pixel_put(screen, x, y, 0x8B4513);
		else if (y < screen->screen_size_height && (y <= mini->start_y || y >= mini->end_y))
			my_mlx_pixel_put(screen, x, y, 0x228B22);
		y++;
	}
}

void	draw_wall_column(t_raycast *cast, t_mlx *screen, t_mini_map *mini, int x)
{
	int	y;

	y = 0;
	if (x >= mini->start_x && x < mini->end_x)
	{
		ft_print_mini_map(cast, screen, mini, x, y);
		return ;
	}
	while(y < screen->screen_size_height)
	{
		if (y < cast->draw_start)
			my_mlx_pixel_put(screen, x, y, 0x87CEEB);
		else if (y <= cast->draw_end)
			my_mlx_pixel_put(screen, x, y, 0x8B4513);
		else if (y < screen->screen_size_height)
			my_mlx_pixel_put(screen, x, y, 0x228B22);
		y++;
	}
}

//void 	draw_rayon(t_map *map, t_mlx *screen, t_player *play, t_direction *dir)
//{
//	int	x;
//	int i;
//	double camera_x;
//	double	ray_dir_x;
//	double ray_dir_y;
//	double ray_x;
//	double ray_y;
//	int map_x;
//	int map_y;
//	int step = 20;

//	x = 0;
//	i = 0;
//	ray_x = play->pos_col;
//	ray_y = play->pos_row;
//	while(x < screen->screen_size_width)
//	{
//		i = 0;
//		x += step;
//		camera_x = 2.0 * x / (double)screen->screen_size_width - 1.0;
//		ray_dir_x = dir->dir_x + dir->plan_x * camera_x;
//		ray_dir_y = dir->dir_y + dir->plan_y * camera_x;
//		ray_x = play->pos_col;
//		ray_y = play->pos_row;
//		while (i < 150)
//		{
//			ray_x += ray_dir_x * 0.05;
//			ray_y += ray_dir_y * 0.05;
//			map_x = (int)ray_x;
//			map_y = (int)ray_y;
//			if (map_x < 0 || map_y < 0 || map_x >= map->cols || map_y >= map->rows)
//				break;
//			if (map->big_map[map_y][map_x] == '1')
//				break;
//			my_mlx_pixel_put(screen, 20 + 100 + (ray_x - play->pos_col) * 10, 20 + 100 + (ray_y - play->pos_row) * 10, 808080);
//			i++;
//		}
//	}
//}

void draw_ray_minimap(t_map *map, t_mlx *screen, t_player *play, t_game *game)
{
	double ray_x;
	double ray_y;
	int map_x;
	int map_y;
	int i;
	
	i = 0;
	ray_x = play->pos_col;
	ray_y = play->pos_row;
	while (i < 150) // longueur max du rayon 
	{
		ray_x += game->dir.dir_x * 0.05;
		ray_y += game->dir.dir_y * 0.05;
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		if (map_x < 0 || map_y < 0 || map_x >= map->cols || map_y >= map->rows)
			break;
		if (map->big_map[map_y][map_x] == '1')
			break;
		my_mlx_pixel_put(screen, 25 + 100 + (ray_x - play->pos_col) * 10,
			25 + 100 + (ray_y - play->pos_row) * 10, 0xFF0000);
		i++;
	}
}



void 	draw_rayon(t_map *map, t_player *play, t_raycast *cast, t_game *game)
{
	int map_x;
	int map_y;
	int hit;
	double delta_dist_x;
	double delta_dist_y;
	int step_x;
	int step_y;
	double side_dist_x;
	double side_dist_y;
	
	hit = 0;
	map_x = (int)play->pos_col;
	map_y = (int)play->pos_row;
	delta_dist_x = fabs(1.0 / cast->ray_dir_x);
	delta_dist_y = fabs(1.0 / cast->ray_dir_y);
	//if (cast->ray_dir_x == 0)
	//	delta_dist_x = 1e30;
	//else
	//	cast->delta_dist_x = fabs(1 / cast->ray_dir_x);
	//if (cast->ray_dir_y == 0)
	//	cast->delta_dist_y = 1e30;
	//else
	//	cast->delta_dist_y = fabs(1 / cast->ray_dir_y);
	if (cast->ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (play->pos_col - map_x)
			* delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - play->pos_col)
			* delta_dist_x;
	}
	if (cast->ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (play->pos_row - map_y)
			* delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - play->pos_row)
			* delta_dist_y;
	}
	while (hit == 0)
	{
		if (map_x < 0 || map_y < 0)
			break ;
		if (map_y >= map->rows
			|| map_x >= map->cols)
			break ;
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
		}
		if (map->big_map[map_y][map_x] == '1')
			hit = 1;
	}
	draw_ray_minimap(map, &game->screen, play, game);
}

void	draw_wall_mini_map(t_player *play, t_map *map, t_mlx *screen, int y)
{
	int map_x;
	int map_y;
	int x;
	
	x = 0;
	while(y < 200)
	{
		x = 0;
		while(x < 200)
		{
			map_x = play->pos_col + (x / 10) - 10;
			map_y = play->pos_row + (y / 10) - 10;
			if (map_x < 0 || map_y < 0 || map_x >= map->cols || map_y >= map->rows)
				my_mlx_pixel_put(screen, 20 + x, 20 + y, 0);
			else if (map->big_map[map_y][map_x] == '1')
				my_mlx_pixel_put(screen, 20 + x, 20 + y, 0);
			else if (map->big_map[map_y][map_x] == '0')
				my_mlx_pixel_put(screen, 20 + x, 20 + y, 0xFFFFFF);
			x++;
		}
		y++;
	}
	
}

void draw_mini_map( t_mlx *screen, t_player *play, t_direction *dir, t_game *game)
{
	int i;
	int j;

	draw_wall_mini_map(play, &game->map, screen, 0);
	i = -3;
	while (i <= 3)
	{
		j = -3;
		while (j <= 3)
		{
			my_mlx_pixel_put(screen, 25 + 100 + j, 25 + 100 + i, 0xFF0000);
			j++;
		}
		i++;
	}
	draw_rayon(&game->map, play, &game->cast, game);
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
		wall_height_calcul(cast, &game->screen);
		draw_wall_column(cast, &game->screen, &game->mini, i);
		i++;
	}
	draw_mini_map(&game->screen, &game->player, &game->dir, game);
}
