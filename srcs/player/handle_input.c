/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:08:42 by skuor             #+#    #+#             */
/*   Updated: 2026/01/22 14:36:14 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	mlx_mouse_hide_no_leak(void *mlx, void *win)
{
	t_xvar		*xvar;
	t_win_list	*xwin;

	if (mlx == NULL || win == NULL)
		return ;
	xvar = (t_xvar *)mlx;
	xwin = (t_win_list *)win;
	XFixesHideCursor(xvar->display, xwin->window);
}

static void	mlx_mouse_show_no_leak(void *mlx, void *win)
{
	t_xvar		*xvar;
	t_win_list	*xwin;

	if (mlx == NULL || win == NULL)
		return ;
	xvar = (t_xvar *)mlx;
	xwin = (t_win_list *)win;
	XFixesShowCursor(xvar->display, xwin->window);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == XK_Left)
		game->dir.turn_left = false;
	if (keycode == XK_Right)
		game->dir.turn_right = false;
	if (keycode == XK_w)
		game->dir.forward = false;
	if (keycode == XK_s)
		game->dir.backward = false;
	if (keycode == XK_a)
		game->dir.strafe_l = false;
	if (keycode == XK_d)
		game->dir.strafe_r = false;
	return (0);
}

static void	mouse_lock(t_game *game)
{
	game->mouse.lock = !game->mouse.lock;
	if (game->mouse.lock == true)
	{
		game->mouse.init = false;
		mlx_mouse_hide_no_leak(game->screen.mlx_ptr, game->screen.win_ptr);
		mlx_mouse_move(game->screen.mlx_ptr, game->screen.win_ptr,
			game->mouse.center_x, game->mouse.center_y);
	}
	else
		mlx_mouse_show_no_leak(game->screen.mlx_ptr, game->screen.win_ptr);
}

int	keyboard_key(int keycode, t_game *game)
{
	if (keycode == 65307)
		on_destroy(game);
	if (keycode == XK_Left)
		game->dir.turn_left = true;
	if (keycode == XK_Right)
		game->dir.turn_right = true;
	if (keycode == XK_w)
		game->dir.forward = true;
	if (keycode == XK_s)
		game->dir.backward = true;
	if (keycode == XK_a)
		game->dir.strafe_l = true;
	if (keycode == XK_d)
		game->dir.strafe_r = true;
	if (keycode == XK_m)
		mouse_lock(game);
	return (0);
}
