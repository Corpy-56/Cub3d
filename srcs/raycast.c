/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:10:23 by agouin            #+#    #+#             */
/*   Updated: 2026/01/14 17:01:19 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config	*calcul_delta_dist(t_config *co)
{
	if (co->cast.ray_dir_x == 0)
		co->cast.delta_dist_x = 1e30;
	else
		co->cast.delta_dist_x = fabs(1 / co->cast.ray_dir_x);
	if (co->cast.ray_dir_y == 0)
		co->cast.delta_dist_y = 1e30;
	else
		co->cast.delta_dist_y = fabs(1 / co->cast.ray_dir_y);
	if (co->cast.ray_dir_x < 0)
	{
		co->cast.step_x = -1;
		co->cast.side_dist_x = (co->dir.pos_x - co->cast.map_x)
			* co->cast.delta_dist_x;
	}
	else
	{
		co->cast.step_x = 1;
		co->cast.side_dist_x = (co->cast.map_x + 1.0 - co->dir.pos_x)
			* co->cast.delta_dist_x;
	}
	return (co);
}

t_config	*radius_calcul(t_config *co)
{
	co->cast.ray_dir_x = co->dir.dir_x + co->dir.plan_x * co->cast.camera;
	co->cast.ray_dir_y = co->dir.dir_y + co->dir.plan_y * co->cast.camera;
	co = calcul_delta_dist(co);
	if (co->cast.ray_dir_y < 0)
	{
		co->cast.step_y = -1;
		co->cast.side_dist_y = (co->dir.pos_y - co->cast.map_y)
			* co->cast.delta_dist_y;
	}
	else
	{
		co->cast.step_y = 1;
		co->cast.side_dist_y = (co->cast.map_y + 1.0 - co->dir.pos_y)
			* co->cast.delta_dist_y;
	}
	return (co);
}

t_config	*wall_height_calcul(t_config *co)
{
	co->cast.line_height = (int)(co->screen.screen_size_height
			/ co->cast.wall_distance);
	co->cast.draw_start = -co->cast.line_height
		/ 2 + co->screen.screen_size_height / 2;

	if (co->cast.draw_start < 0)
		co->cast.draw_start = 0;
	co->cast.draw_end = co->cast.line_height
		/ 2 + co->screen.screen_size_height / 2;
	if (co->cast.draw_end >= co->screen.screen_size_height)
		co->cast.draw_end = co->screen.screen_size_height -1;
	return (co);
}

t_config	*hit_wall_boucle(t_config *co)
{
	while (co->cast.hit == 0)
	{
		if (co->cast.map_x < 0 || co->cast.map_y < 0)
			break ;
		if (co->cast.map_y >= co->map.map_height
			|| co->cast.map_x >= co->map.map_width)
			break ;
		if (co->cast.side_dist_x < co->cast.side_dist_y)
		{
			co->cast.side_dist_x += co->cast.delta_dist_x;
			co->cast.map_x += co->cast.step_x;
			co->cast.side = 0;
		}
		else
		{
			co->cast.side_dist_y += co->cast.delta_dist_y;
			co->cast.map_y += co->cast.step_y;
			co->cast.side = 1;
		}
		if (co->map.big_map[co->cast.map_y][co->cast.map_x] == '1')
			co->cast.hit = 1;
	}
	return (co);
}


void	my_mlx_pixel_put(t_config *config, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= config->screen.screen_size_width || y >= config->screen.screen_size_height)
		return;
	dst = config->screen.addr + (y * config->screen.line_len + x * (config->screen.bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_print_mini_map(t_config *c, int x, int y)
{
	int i;

	i = 0;
	while(y < c->screen.screen_size_height)
	{
		if(y >= c->mini.start_y && y <= c->mini.end_y)
			i++;
		else if (y < c->cast.draw_start && (y <= c->mini.start_y || y >= c->mini.end_y))
			my_mlx_pixel_put(c, x, y, 0x87CEEB);
		else if (y <= c->cast.draw_end && (y <= c->mini.start_y || y >= c->mini.end_y))
			my_mlx_pixel_put(c, x, y, 0x8B4513);
		else if (y < c->screen.screen_size_height && (y <= c->mini.start_y || y >= c->mini.end_y))
			my_mlx_pixel_put(c, x, y, 0x228B22);
		y++;
	}
}

void	draw_wall_column(t_config *c, int x)
{
	int	y;

	y = 0;
	if (x >= c->mini.start_x && x <= c->mini.end_x)
	{
		ft_print_mini_map(c, x, y);
		return ;
	}
	while(y < c->screen.screen_size_height)
	{
		if (y < c->cast.draw_start)
			my_mlx_pixel_put(c, x, y, 0x87CEEB);
		else if (y <= c->cast.draw_end)
			my_mlx_pixel_put(c, x, y, 0x8B4513);
		else if (y < c->screen.screen_size_height)
			my_mlx_pixel_put(c, x, y, 0x228B22);
		y++;
	}
}

void draw_mini_map(t_config *co)
{
	int y;
	int i;
	int j;
	int map_x;
	int map_y;
	int x;

	y = 0;
	while(y <= 300)
	{
		x = 0;
		while(x <= 300)
		{
			map_x = co->map.player_x + (x / 10) - 15;
			map_y = co->map.player_y + (y / 10) - 15;
			if (map_x < 0 || map_y < 0 || map_x >= co->map.map_width || map_y >= co->map.map_height)
				my_mlx_pixel_put(co, 10 + x, 10 + y, 0);
			else if (co->map.big_map[map_y][map_x] == '1')
				my_mlx_pixel_put(co, 10 + x, 10 + y, 0);
			else if (co->map.big_map[map_y][map_x] == '0')
				my_mlx_pixel_put(co, 10 + x, 10 + y, 0xFFFFFF);
			x++;
		}
		y++;
		 i = -3;
    	while (i <= 3)
		{
			j = -3;
			while (j <= 3)
			{
				my_mlx_pixel_put(co, 10 + 300 / 2 + j, 10 + 300 / 2 + i, 0xFF0000);
				j++;
			}
			i++;
		}
	}
}

void	raycast(t_config *co)
{
	int	i;

	ft_init_ray(co);
	i = 0;
	while (i < co->screen.screen_size_width)
	{
		co->cast.hit = 0;
		co->cast.map_x = (int)co->dir.pos_x;
		co->cast.map_y = (int)co->dir.pos_y;
		co->cast.camera = 2.0 * i / (double)co->screen.screen_size_width - 1.0;
		co = radius_calcul(co);
		co = hit_wall_boucle(co);
		if (co->cast.side == 0)
			co->cast.wall_distance = co->cast.side_dist_x
				- co->cast.delta_dist_x;
		else
			co->cast.wall_distance = co->cast.side_dist_y
				- co->cast.delta_dist_y;
		if (co->cast.wall_distance <= 0.0001)
			co->cast.wall_distance = 0.0001;
		co = wall_height_calcul(co);
		draw_wall_column(co, i);
		i++;
	}
	draw_mini_map(co);
}
