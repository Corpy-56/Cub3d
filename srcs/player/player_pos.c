/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:58:18 by skuor             #+#    #+#             */
/*   Updated: 2026/01/14 18:41:35 by skuor            ###   ########.fr       */
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
				ft_printf("PLAYER POSITION (%d, %d)\n", (player->pos_col + 1), (player->pos_row + 1));
				ft_printf("PLAYER POSITION (col, row)\n");
				ft_printf("Spawn orientation: %c\n", player->spawn_dir);
				map[y][x] = '0';
				ft_print_map(map);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

