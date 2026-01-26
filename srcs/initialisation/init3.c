/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:20:46 by agouin            #+#    #+#             */
/*   Updated: 2026/01/26 16:37:47 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_destroy(t_game *game)
{
	free_all(game);
	if (game->screen.img)
		mlx_destroy_image(game->screen.mlx_ptr, game->screen.img);
	if (game->tex.img_n)
		mlx_destroy_image(game->screen.mlx_ptr, game->tex.img_n);
	if (game->tex.img_s)
		mlx_destroy_image(game->screen.mlx_ptr, game->tex.img_s);
	if (game->tex.img_e)
		mlx_destroy_image(game->screen.mlx_ptr, game->tex.img_e);
	if (game->tex.img_w)
		mlx_destroy_image(game->screen.mlx_ptr, game->tex.img_w);
	if (game->screen.win_ptr)
		mlx_destroy_window(game->screen.mlx_ptr, game->screen.win_ptr);
	if (game->screen.mlx_ptr)
	{
		mlx_destroy_display(game->screen.mlx_ptr);
		free(game->screen.mlx_ptr);
	}
	exit(0);
	return (0);
}

void	ft_init_ray(t_raycast *cast, t_mini_map *mini)
{
	cast->camera = 0.0;
	cast->ray_dir_x = 0.0;
	cast->ray_dir_y = 0.0;
	cast->side_dist_x = 0.0;
	cast->side_dist_y = 0.0;
	cast->delta_dist_x = 0.0;
	cast->delta_dist_y = 0.0;
	cast->wall_distance = 0.0;
	cast->step_x = 0;
	cast->step_y = 0;
	cast->draw_start = 0;
	cast->draw_end = 0;
	cast->hit = 0;
	cast->side = 0;
	cast->map_x = 0;
	cast->line_height = 0;
	cast->map_y = 0;
	mini->start_x = 20;
	mini->end_x = 220;
	mini->start_y = 20;
	mini->end_y = 220;
}

void	init_tex_1(t_texture *tex, t_game *game)
{
	int	y;
	int	x;

	y = 64;
	x = 64;
	tex->tex_x = 0;
	tex->tex_y = 0;
	tex->test = 0.0;
	tex->t_lar = 0;
	tex->wall_t = 0.0;
	tex->img_n = mlx_xpm_file_to_image(game->screen.mlx_ptr,
			game->config.no_path, &y, &x);
	tex->img_s = mlx_xpm_file_to_image(game->screen.mlx_ptr,
			game->config.so_path, &y, &x);
	tex->img_e = mlx_xpm_file_to_image(game->screen.mlx_ptr,
			game->config.ea_path, &y, &x);
	tex->img_w = mlx_xpm_file_to_image(game->screen.mlx_ptr,
			game->config.we_path, &y, &x);
	if (!tex->img_n || !tex->img_w || !tex->img_e || !tex->img_s)
		ft_error(2, NULL, "Probleme with asset\n");
}

void	ft_init_screen(t_game *g, t_mlx *screen)
{
	g->color.int_floor = rgb_to_int(g->floor.r, g->floor.g, g->floor.b);
	g->color.int_ceiling = rgb_to_int(g->ceiling.r, g->ceiling.g, g->ceiling.b);
	ft_bzero(screen, sizeof(t_mlx));
	screen->mlx_ptr = mlx_init();
	// screen->mlx_ptr = NULL;
	if (screen->mlx_ptr == NULL)
	{
		on_destroy(g);
	}
	//ft_error(0, NULL, "Mlx_init failed\n");
	mlx_get_screen_size(screen->mlx_ptr, &screen->screen_size_width,
		&screen->screen_size_height);
	init_tex_1(&g->tex, g);
	g->mouse.center_x = g->screen.screen_size_width / 2;
	g->mouse.center_y = g->screen.screen_size_height / 2;
	screen->win_ptr = mlx_new_window(screen->mlx_ptr,
			screen->screen_size_width, screen->screen_size_height, "Cub3d");
	screen->img = mlx_new_image(screen->mlx_ptr,
			screen->screen_size_width, screen->screen_size_height);
	screen->addr = mlx_get_data_addr(screen->img, &screen->bpp,
			&screen->line_len, &screen->endian);
}

void	init_mouse(t_mouse *mouse)
{
	mouse->init = false;
	mouse->sens = 0.01;
	mouse->lock = false;
	mouse->last_x = 0;
	mouse->x = 0;
	mouse->y = 0;
}
