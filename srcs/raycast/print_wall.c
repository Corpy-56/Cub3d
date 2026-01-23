/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:09:07 by agouin            #+#    #+#             */
/*   Updated: 2026/01/23 17:08:54 by agouin           ###   ########.fr       */
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

int	ft_get_color(t_texture *tex, int y, int x, char o)
{
	char	*c;

	if (o == 'N')
		tex->addr = mlx_get_data_addr(tex->img_n, &tex->bpp,
				&tex->line_len, &tex->endian);
	if (o == 'W')
		tex->addr = mlx_get_data_addr(tex->img_w, &tex->bpp,
				&tex->line_len, &tex->endian);
	if (o == 'E')
		tex->addr = mlx_get_data_addr(tex->img_e, &tex->bpp,
				&tex->line_len, &tex->endian);
	if (o == 'S')
		tex->addr = mlx_get_data_addr(tex->img_s, &tex->bpp,
				&tex->line_len, &tex->endian);
	c = tex->addr + (y * tex->line_len) + x * (tex->bpp / 8);
	return (*(int *)c);
}

void	ft_draw_texture_2(t_game *game, t_raycast *cast, int x, int y)
{
	int	color;

	color = 0;
	if (cast->ray_dir_y > 0)
	{
		game->tex.tex_y = (int)game->tex.tex_pos & 63;
		color = ft_get_color(&game->tex, game->tex.tex_y, game->tex.tex_x, 'S');
		my_mlx_pixel_put(&game->screen, x, y, color);
		game->tex.tex_pos += game->tex.step;	
	}
	else
	{
		game->tex.tex_y = (int)game->tex.tex_pos & 63;
		color = ft_get_color(&game->tex, game->tex.tex_y, game->tex.tex_x, 'N');
		my_mlx_pixel_put(&game->screen, x, y, color);
		game->tex.tex_pos += game->tex.step;
	}		
}

void	ft_draw_texture(t_game *game, t_raycast *cast, int x, int y)
{
	int	color;

	color = 0;
	if (cast->side == 0)
	{
		if (cast->ray_dir_x > 0)
		{
			game->tex.tex_y = (int)game->tex.tex_pos & 63;
			color = ft_get_color(&game->tex, game->tex.tex_y,
					game->tex.tex_x, 'E');
			my_mlx_pixel_put(&game->screen, x, y, color);
			game->tex.tex_pos += game->tex.step;
		}
		else
		{
			game->tex.tex_y = (int)game->tex.tex_pos & 63;
			color = ft_get_color(&game->tex, game->tex.tex_y,
					game->tex.tex_x, 'W');
			my_mlx_pixel_put(&game->screen, x, y, color);
			game->tex.tex_pos += game->tex.step;
		}		
	}
	else
		ft_draw_texture_2(game, cast, x, y);
}

void	draw_wall_column(t_raycast *cast, t_mlx *scre, int x, t_game *game)
{
	int	y;

	y = 0;
	game->tex.step = 1.0 * 64 / cast->line_height;
	game->tex.tex_pos = (cast->draw_start - scre->screen_size_height
			/ 2 + cast->line_height / 2) * game->tex.step;
	if (cast->side == 0 && cast->ray_dir_x > 0)// a voir permet de mettre les images a lendroit 
		game->tex.tex_x = 64 - game->tex.tex_x - 1;
	if (cast->side == 1 && cast->ray_dir_y < 0)
		game->tex.tex_x = 64 - game->tex.tex_x - 1;
	while (y < scre->screen_size_height)
	{
		if (y < cast->draw_start)
			my_mlx_pixel_put(scre, x, y, 0x87CEEB);
		else if (y <= cast->draw_end)
			ft_draw_texture(game, cast, x, y);
		else if (y < scre->screen_size_height)
			my_mlx_pixel_put(scre, x, y, 0x228B22);
		y++;
	}
}
