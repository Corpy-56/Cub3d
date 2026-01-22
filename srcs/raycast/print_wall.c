/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:09:07 by agouin            #+#    #+#             */
/*   Updated: 2026/01/22 16:21:03 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *screen, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= screen->screen_size_width
		|| y >= screen->screen_size_height)
		return ;
	dst = screen->addr + (y * screen->line_len + x * (screen->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_wall_column(t_raycast *cast, t_mlx *scre, t_mini_map *mini, int x)
{
	int	y;

	y = 0;
	if (x >= mini->start_x && x < mini->end_x)
	{
		ft_print_mini_map(cast, scre, mini, x);
		return ;
	}
	while (y < scre->screen_size_height)
	{
		if (y < cast->draw_start)
			my_mlx_pixel_put(scre, x, y, 0x87CEEB);
		else if (y <= cast->draw_end)
			my_mlx_pixel_put(scre, x, y, 0x8B4513);
		else if (y < scre->screen_size_height)
			my_mlx_pixel_put(scre, x, y, 0x228B22);
		y++;
	}
}
