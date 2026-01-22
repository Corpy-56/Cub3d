/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:20:46 by agouin            #+#    #+#             */
/*   Updated: 2026/01/22 16:31:22 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_destroy(t_game *game)
{
	free_all(game);
	if (game->screen.img)
		mlx_destroy_image(game->screen.mlx_ptr, game->screen.img);
	mlx_destroy_window(game->screen.mlx_ptr, game->screen.win_ptr);
	mlx_destroy_display(game->screen.mlx_ptr);
	free(game->screen.mlx_ptr);
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

void	ft_init_screen(t_mlx *screen)
{
	screen->mlx_ptr = mlx_init();
	if (screen->mlx_ptr == NULL)
		ft_error(0, NULL, "Mlx_init failed\n");
	mlx_get_screen_size(screen->mlx_ptr, &screen->screen_size_width,
		&screen->screen_size_height);
	screen->screen_size_width = 1920;
	screen->screen_size_height = 1080;
	screen->win_ptr = mlx_new_window(screen->mlx_ptr,
			screen->screen_size_width, screen->screen_size_height, "Cub3d");
	screen->img = mlx_new_image(screen->mlx_ptr,
			screen->screen_size_width, screen->screen_size_height);
	screen->addr = mlx_get_data_addr(screen->img, &screen->bpp,
			&screen->line_len, &screen->endian);
}
