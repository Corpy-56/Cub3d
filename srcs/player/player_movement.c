/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:30:10 by skuor             #+#    #+#             */
/*   Updated: 2026/01/19 12:05:19 by skuor            ###   ########.fr       */
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

static long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

int	watching_left_right(void *dir) // debug
{
	double		new_angle;
	t_direction	*d;
	double	angle_before;
	long	now;
	static long	last_print_ms = 0;


	d = (t_direction *)dir;
	angle_before = d->angle;
	new_angle = angle_before;
	d->rot_speed = 0.05;
	if (d->turn_left)
		new_angle -= d->rot_speed;
	if (d->turn_right)
		new_angle += d->rot_speed;
	new_angle = normalize_angle(new_angle);
	d->angle = new_angle;
	now = now_ms();
	if (now - last_print_ms >= 100) /* 100ms = 10/s */
	{
		printf("L=%d R=%d | before=%.3f -> after=%.3f\n",
			(int)d->turn_left, (int)d->turn_right,
			angle_before, d->angle);
		last_print_ms = now;
	}
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
