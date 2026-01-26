/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:07:56 by agouin            #+#    #+#             */
/*   Updated: 2026/01/26 11:40:30 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_mini_map(t_raycast *cast, t_mlx *scre, t_mini_map *mini, int x)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (y < scre->screen_size_height)
	{
		if (y >= mini->start_y && y < mini->end_y)
			i++;
		else if (y < cast->draw_start
			&& (y <= mini->start_y || y >= mini->end_y))
			my_mlx_pixel_put(scre, x, y, 0x87CEEB);
		else if (y <= cast->draw_end
			&& (y <= mini->start_y || y >= mini->end_y))
			my_mlx_pixel_put(scre, x, y, 0x8B4513);
		else if (y < scre->screen_size_height
			&& (y <= mini->start_y || y >= mini->end_y))
			my_mlx_pixel_put(scre, x, y, 0x228B22);
		y++;
	}
}

void	draw_wall_mini_map_2(t_player *play, t_map *map, t_mlx *screen, int y)
{
	int	map_x;
	int	map_y;
	int	x;

	x = 0;
	while (y < 200)
	{
		x = 0;
		while (x < 200)
		{
			map_x = play->pos_col + (x / 10) - 10;
			map_y = play->pos_row + (y / 10) - 10;
			if (map_x < 0 || map_y < 0 || map_x >= map->cols
				|| map_y >= map->rows)
				my_mlx_pixel_put(screen, 20 + x, 20 + y, 0);
			else if (map->big_map[map_y][map_x] == '1')
				my_mlx_pixel_put(screen, 20 + x, 20 + y, 0);
			x++;
		}
		y++;
	}
}

void	draw_rayon(t_map *map, t_player *play, t_mlx *screen, t_game *game)
{
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	int		i;

	i = 0;
	ray_x = play->pos_col;
	ray_y = play->pos_row;
	while (i < 193)
	{
		ray_x += game->dir.dir_x * 0.05;
		ray_y += game->dir.dir_y * 0.05;
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		if (map_x < 0 || map_y < 0 || map_x >= map->cols || map_y >= map->rows)
			break ;
		if (map->big_map[map_y][map_x] == '1')
			break ;
		my_mlx_pixel_put(screen, 25 + 100 + (ray_x - play->pos_col) * 10,
			25 + 100 + (ray_y - play->pos_row) * 10, 0xFF0000);
		i++;
	}
	draw_wall_mini_map_2(play, map, screen, 0);
}

void	draw_wall_mini_map(t_player *play, t_map *map, t_mlx *screen, t_game *game)
{
	int	map_x;
	int	map_y;
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y++ < 200)
	{
		x = 0;
		while (x < 200)
		{
			map_x = play->pos_col + (x / 10) - 10;
			map_y = play->pos_row + (y / 10) - 10;
			if (map_x < 0 || map_y < 0 || map_x >= map->cols
				|| map_y >= map->rows)
				my_mlx_pixel_put(screen, 20 + x, 20 + y, 0);
			else if (map->big_map[map_y][map_x] == '0')
				my_mlx_pixel_put(screen, 20 + x, 20 + y, 0xFFFFFF);
			else
				my_mlx_pixel_put(screen, 20 + x, 20 + y, 0);
			x++;
		}
	}
	draw_rayon(map, play, screen, game);
}

void	draw_mini_map( t_mlx *screen, t_player *play, t_game *game)
{
	int	i;
	int	j;

	draw_wall_mini_map(play, &game->map, screen, game);
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
