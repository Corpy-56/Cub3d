/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:25:31 by agouin            #+#    #+#             */
/*   Updated: 2026/01/26 13:26:19 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hit_wall_boucle(t_raycast *cast, t_game *game)
{
	while (cast->hit == 0)
	{
		if (cast->map_x < 0 || cast->map_y < 0)
			break ;
		if (cast->map_y >= game->map.rows
			|| cast->map_x >= game->map.cols)
			break ;
		if (cast->side_dist_x < cast->side_dist_y)
		{
			cast->side_dist_x += cast->delta_dist_x;
			cast->map_x += cast->step_x;
			cast->side = 0;
		}
		else
		{
			cast->side_dist_y += cast->delta_dist_y;
			cast->map_y += cast->step_y;
			cast->side = 1;
		}
		if (game->map.big_map[cast->map_y][cast->map_x] == '1')
			cast->hit = 1;
	}
	return ;
}
