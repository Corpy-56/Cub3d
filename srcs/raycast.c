/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:10:23 by agouin            #+#    #+#             */
/*   Updated: 2026/01/13 16:28:50 by agouin           ###   ########.fr       */
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
	//printf("%d - %d\n", co->cast.map_y, co->cast.map_x);
	//printf("%d - %d\n", co->map.map_height, co->map.map_width);
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
		//printf("%d - %d\n", co->cast.map_y, co->cast.map_x);
		if (co->map.big_map[co->cast.map_y][co->cast.map_x] == '1')
			co->cast.hit = 1;
		//printf("start cell = %c\n", co->map.big_map[co->cast.map_y][co->cast.map_x]);
	}
	return (co);
}

//void	draw_vertical_line(t_config *config, int x, int start, int end, int color)
//{
//	int y;

//	y = start;
//	//config->screen.image_wall = mlx_get_data_addr(config->screen.image_wall, &config->screen.bpp, &config->screen.line_len, &config->screen.endian);
//	while (y <= end)
//	{
//		//my_mlx_pixel_put(config, x, y, color);
//		//mlx_pixel_put(config->screen.mlx_ptr, config->screen.win_ptr, x, y, color);
//		//mlx_put_image_to_window(config->screen.mlx_ptr, config->screen.win_ptr, config->screen.image_wall,
//		//	x * 1, y * 1);
//		my_mlx_pixel_put(config, x, y, color);
//		y++;
//	}
//}


void	my_mlx_pixel_put(t_config *config, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= config->screen.screen_size_width || y >= config->screen.screen_size_height)
		return;
	dst = config->screen.addr + (y * config->screen.line_len + x * (config->screen.bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_wall_column(t_config *c, int x)
{
	int	y;

	y = 0;
	//printf("%d\n", c->cast.draw_start);
//	printf("%d\n", c->cast.draw_end);
	while (y < c->cast.draw_start)
	{
	//	printf("A");
		my_mlx_pixel_put(c, x, y, 0x87CEEB); // bleu ciel
		y++;
	}
	while (y <= c->cast.draw_end)
	{
		my_mlx_pixel_put(c, x, y, 0x8B4513); // marron
		y++;
	}
	while (y < c->screen.screen_size_height)
	{
	//	printf("b");
		my_mlx_pixel_put(c, x, y, 0x228B22); // vert
		y++;
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
		//printf("ray=(%f,%f) side=%d dist=%f\n", co->cast.ray_dir_x, co->cast.ray_dir_y, co->cast.side, co->cast.wall_distance);
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
	//	printf("dist = %f\n", co->cast.wall_distance);
		co = wall_height_calcul(co);
		draw_wall_column(co, i);
		//draw_vertical_line(co, i, co->cast.draw_start, co->cast.draw_end, 0xFFFFFF);
	//draw_vertical_line(co, i, co->cast.draw_start, co->cast.draw_end, (i % 2) ? 0xFF0000 : 0x00FF00);
		i++;
	}
	mlx_put_image_to_window(co->screen.mlx_ptr, co->screen.win_ptr,	co->screen.img, 0, 0);
}
