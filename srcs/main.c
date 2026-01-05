/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:50:57 by skuor             #+#    #+#             */
/*   Updated: 2026/01/05 17:16:59 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	on_destroy(t_config *game)
{
	//free_image(game);
	mlx_destroy_window(game->screen.mlx_ptr, game->screen.win_ptr);
	mlx_destroy_display(game->screen.mlx_ptr);
	//free(game.screen.mlx_ptr);
	//if (game->big_map != NULL || game->big_map->map != NULL)
	//{
	//	ft_free_tab(game->big_map->map);
	//	free(game->big_map);
	//	free(game);
	//}
	exit(0);
	return (0);
}

int	keyboard_key(int keycode, t_config *game)//ici ca va etre les touches jouer
{
	if (keycode == 65307)
		on_destroy(game);
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

void	ft_init_screen(t_mlx *screen)
{
	screen->mlx_ptr = mlx_init();
	if (screen->mlx_ptr == NULL)
		ft_error(0, NULL, "Mlx_init failed\n");
	mlx_get_screen_size(screen->mlx_ptr, &screen->screen_size_width,
		&screen->screen_size_height);
	screen->win_ptr = mlx_new_window(screen->mlx_ptr, screen->screen_size_width, screen->screen_size_height, "Cub3d");
}

int	main(int argc, char **argv)
{
	t_config	config;

	init_config(&config);
	check_args(argc, argv);
	//if (!parsing_file(argv[1], &config))
	//	return (ft_printf("Error parsing file\n"), 1);
	ft_init_screen(&config.screen);
	mlx_key_hook(config.screen.win_ptr, keyboard_key, &config);
	mlx_hook(&config.screen.win_ptr, 17, 0, on_destroy, &config);
	mlx_loop(config.screen.mlx_ptr);
	return (0);
}