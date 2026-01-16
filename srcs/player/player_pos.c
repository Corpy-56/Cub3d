/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:58:18 by skuor             #+#    #+#             */
/*   Updated: 2026/01/16 15:07:51 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_player(char **map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'E'
				|| map[y][x] == 'W' || map[y][x] == 'S')
			{
				player->pos_col = x;
				player->pos_row = y;
				player->spawn_dir = map[y][x];
				map[y][x] = '0';
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

