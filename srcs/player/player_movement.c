/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:30:10 by skuor             #+#    #+#             */
/*   Updated: 2026/01/20 14:39:25 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > (2 * PI))
		angle -= 2 * PI;
	return (angle);
}

// static long	now_ms(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
// }

// int	watching_left_right(void *game) // debug
// {
// 	double		new_angle;
// 	// t_direction	*d;
// 	t_game	*g;
// 	double	angle_before;
// 	long	now;
// 	static long	last_print_ms = 0;

// 	g = (t_game *)game;
// 	// d = (t_direction *)dir;
// 	angle_before = g->dir.angle;
// 	new_angle = angle_before;
// 	g->dir.rot_speed = 0.05;
// 	if (g->dir.turn_left)
// 		new_angle -= g->dir.rot_speed;
// 	if (g->dir.turn_right)
// 		new_angle += g->dir.rot_speed;
// 	new_angle = normalize_angle(new_angle);
// 	g->dir.angle = new_angle;
// 	now = now_ms();
// 	if (now - last_print_ms >= 100) /* 100ms = 10/s */
// 	{
// 		printf("L=%d R=%d | before=%.3f -> after=%.3f\n",
// 			(int)g->dir.turn_left, (int)g->dir.turn_right,
// 			angle_before, g->dir.angle);
// 		last_print_ms = now;
// 	}
// 	raycast(g, &g->cast);
// 	mlx_put_image_to_window(g->screen.mlx_ptr, g->screen.win_ptr, g->screen.img, 0, 0);

// 	return (0);
// }

int	watching_left_right(void *game)
{
	double		new_angle;
	t_game		*g;

	g = (t_game *)game;
	g->dir.plane_len = tan(FOV / 2);
	new_angle = g->dir.angle;
	g->dir.rot_speed = 0.05;
	if (g->dir.turn_left == true)
		new_angle = g->dir.angle - g->dir.rot_speed;
	if (g->dir.turn_right == true)
		new_angle = g->dir.angle + g->dir.rot_speed;
	new_angle = normalize_angle(new_angle);
	g->dir.angle = new_angle;
	g->dir.dir_x = cos(g->dir.angle);
	g->dir.dir_y = sin(g->dir.angle);
	g->dir.plan_x = (-g->dir.dir_y) * g->dir.plane_len;
	g->dir.plan_y = g->dir.dir_x * g->dir.plane_len;
	raycast(g, &g->cast);
	mlx_put_image_to_window(g->screen.mlx_ptr, g->screen.win_ptr, g->screen.img, 0, 0);
	return (0);
}

// int	watching_left_right(void *dir)
// {
// 	double		new_angle;
// 	t_direction	*d;

// 	d = (t_direction *)dir;
// 	new_angle = d->angle;
// 	d->rot_speed = 0.05;
// 	if (d->turn_left == true)
// 		new_angle = d->angle - d->rot_speed;
// 	if (d->turn_right == true)
// 		new_angle = d->angle + d->rot_speed;
// 	new_angle = normalize_angle(new_angle);
// 	d->angle = new_angle;
// 	return (0);
// }
