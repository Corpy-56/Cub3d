/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:30:10 by skuor             #+#    #+#             */
/*   Updated: 2026/01/16 17:16:17 by skuor            ###   ########.fr       */
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

int	watching_left_right(void *dir)
{
	double		new_angle;
	t_direction	*d;

	d = (t_direction *)dir;
	new_angle = d->angle;
	d->rot_speed = 0.05;
	if (d->turn_left == true)
		new_angle = d->angle - d->rot_speed;
	if (d->turn_right == true)
		new_angle = d->angle + d->rot_speed;
	new_angle = normalize_angle(new_angle);
	d->angle = new_angle;
	return (0);
}



