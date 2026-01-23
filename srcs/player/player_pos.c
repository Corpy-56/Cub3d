/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:58:18 by skuor             #+#    #+#             */
/*   Updated: 2026/01/23 11:23:06 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	find_player(char **map, t_game *game)
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
				game->player.pos_col = x + 0.5;
				game->player.pos_row = y + 0.5;
				game->player.spawn_dir = map[y][x];
				game->dir.angle = convert_angle(map[y][x]);
				calc_dir_plan(&game->dir);
				map[y][x] = '0';
				return (init_map(&game->dir, &game->player));
			}
			x++;
		}
		y++;
	}
	return (0);
}

double	convert_angle(char orientation)
{
	double	angle;

	angle = 0;
	if (orientation == 'N')
		angle = (3 * PI) / 2;
	else if (orientation == 'E')
		angle = 0;
	else if (orientation == 'W')
		angle = PI;
	else if (orientation == 'S')
		angle = PI / 2;
	return (angle);
}
