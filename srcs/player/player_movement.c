/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:30:10 by skuor             #+#    #+#             */
/*   Updated: 2026/01/20 17:37:20 by skuor            ###   ########.fr       */
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

void	calc_dir_plan(t_direction *dir)
{
	dir->dir_x = cos(dir->angle);
	dir->dir_y = sin(dir->angle);
	dir->plan_x = (-dir->dir_y) * dir->plane_len;
	dir->plan_y = dir->dir_x * dir->plane_len;
}

void	watching_left_right(void *game)
{
	t_game		*g;
	double		new_angle;

	g = (t_game *)game;
	new_angle = g->dir.angle;
	// g->dir.rot_speed = 0.05;
	if (!g->dir.turn_left && !g->dir.turn_right)
		return ;
	if (g->dir.turn_left == true)
		new_angle = g->dir.angle - g->dir.rot_speed;
	if (g->dir.turn_right == true)
		new_angle = g->dir.angle + g->dir.rot_speed;
	new_angle = normalize_angle(new_angle);
	g->dir.angle = new_angle;
	calc_dir_plan(&g->dir);
	// raycast(g, &g->cast);
	// mlx_put_image_to_window(g->screen.mlx_ptr,
	// 	g->screen.win_ptr, g->screen.img, 0, 0);
}

void	move_forward_backward(void *game)
{
	t_game	*g;
	double	dx;
	double	dy;
	double	new_x;
	double	new_y;

	g = (t_game *)game;
	dx = g->dir.dir_x * g->dir.move_speed;
	dy = g->dir.dir_y * g->dir.move_speed;
	if (!g->dir.forward && !g->dir.backward)
		return ;
	if (g->dir.forward)
	{
		new_x = g->player.pos_col + dx;
		new_y = g->player.pos_row + dy;
	}
	if (g->dir.backward)
	{
		new_x = g->player.pos_col - dx;
		new_y = g->player.pos_row - dy;
	}
	g->player.pos_col = new_x;
	g->player.pos_row = new_y;
}

int	player_movement(void *game)
{
	t_game	*g;

	g = (t_game *)game;
	watching_left_right(game);
	move_forward_backward(game);
	raycast(g, &g->cast);
	mlx_put_image_to_window(g->screen.mlx_ptr,
		g->screen.win_ptr, g->screen.img, 0, 0);
	return (0);
}
