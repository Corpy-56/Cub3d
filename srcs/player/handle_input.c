/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:08:42 by skuor             #+#    #+#             */
/*   Updated: 2026/01/21 10:24:45 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	return (0);
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
	return (-1);
}
