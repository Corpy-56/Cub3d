/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:08:42 by skuor             #+#    #+#             */
/*   Updated: 2026/01/19 12:06:03 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == XK_Left)
		game->dir.turn_left = false;
	if (keycode == XK_Right)
		game->dir.turn_right = false;
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
	//else if (keycode == 119)
	//	ft_move_w(game);
	//else if (keycode == 115)
	//	ft_move_s(game);
	//else if (keycode == 97)
	//	ft_move_a(game);
	//else if (keycode == 100)
	//	ft_move_d(game);
	return (-1);
}

