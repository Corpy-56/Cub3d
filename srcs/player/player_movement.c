/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:30:10 by skuor             #+#    #+#             */
/*   Updated: 2026/01/22 10:18:30 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	watching_mouse(void	*game)
{
	int		x;
	int		y;
	int		dx;
	t_game	*g;

	g = (t_game *)game;
	x = 0;
	y = 0;
	mlx_mouse_get_pos(g->screen.mlx_ptr, g->screen.win_ptr, &x, &y);
	if (!g->mouse.init)
	{
		g->mouse.last_x = x;
		g->mouse.init = true;
		return ;
	}
	dx = x - g->mouse.last_x;
	g->mouse.last_x = x;
	if (dx == 0)
		return ;
	g->dir.angle = normalize_angle(g->dir.angle + dx * g->mouse.sens);
	calc_dir_plan(&g->dir);
}

void	watching_left_right(void *game)
{
	t_game		*g;
	double		new_angle;

	g = (t_game *)game;
	new_angle = g->dir.angle;
	if (!g->dir.turn_left && !g->dir.turn_right)
		return ;
	if (g->dir.turn_left == true)
		new_angle = g->dir.angle - g->dir.rot_speed;
	if (g->dir.turn_right == true)
		new_angle = g->dir.angle + g->dir.rot_speed;
	new_angle = normalize_angle(new_angle);
	g->dir.angle = new_angle;
	calc_dir_plan(&g->dir);
}

void	move_forward_backward(void *game)
{
	t_game	*g;
	double	new_x;
	double	new_y;

	g = (t_game *)game;
	g->dir.dx = g->dir.dir_x * g->dir.move_speed;
	g->dir.dy = g->dir.dir_y * g->dir.move_speed;
	if ((!g->dir.forward && !g->dir.backward)
		|| (g->dir.forward && g->dir.backward))
		return ;
	if (g->dir.forward)
	{
		new_x = g->player.pos_col + g->dir.dx;
		new_y = g->player.pos_row + g->dir.dy;
	}
	if (g->dir.backward)
	{
		new_x = g->player.pos_col - g->dir.dx;
		new_y = g->player.pos_row - g->dir.dy;
	}
	if (!check_walls(g, new_x, g->player.pos_row))
		g->player.pos_col = new_x;
	if (!check_walls(g, g->player.pos_col, new_y))
		g->player.pos_row = new_y;
}

void	move_strafe(void *game)
{
	t_game	*g;
	double	new_x;
	double	new_y;

	g = (t_game *)game;
	g->dir.sx = -g->dir.dir_y * g->dir.move_speed;
	g->dir.sy = g->dir.dir_x * g->dir.move_speed;
	if ((!g->dir.strafe_l && !g->dir.strafe_r)
		|| (g->dir.strafe_l && g->dir.strafe_r))
		return ;
	if (g->dir.strafe_l)
	{
		new_x = g->player.pos_col - g->dir.sx;
		new_y = g->player.pos_row - g->dir.sy;
	}
	if (g->dir.strafe_r)
	{
		new_x = g->player.pos_col + g->dir.sx;
		new_y = g->player.pos_row + g->dir.sy;
	}
	if (!check_walls(g, new_x, g->player.pos_row))
		g->player.pos_col = new_x;
	if (!check_walls(g, g->player.pos_col, new_y))
		g->player.pos_row = new_y;
}

int	player_movement(void *game)
{
	t_game	*g;

	g = (t_game *)game;
	watching_mouse(game);
	watching_left_right(game);
	move_forward_backward(game);
	move_strafe(game);
	raycast(g, &g->cast);
	mlx_put_image_to_window(g->screen.mlx_ptr,
		g->screen.win_ptr, g->screen.img, 0, 0);
	return (0);
}
