/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:50:57 by skuor             #+#    #+#             */
/*   Updated: 2026/01/16 18:14:58 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_destroy(t_game *game)
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

void	ft_init_screen(t_mlx *screen)
{
	screen->mlx_ptr = mlx_init();
	if (screen->mlx_ptr == NULL)
		ft_error(0, NULL, "Mlx_init failed\n");
	mlx_get_screen_size(screen->mlx_ptr, &screen->screen_size_width,
		&screen->screen_size_height);
	screen->win_ptr = mlx_new_window(screen->mlx_ptr, screen->screen_size_width, screen->screen_size_height, "Cub3d");
	screen->img = mlx_new_image(screen->mlx_ptr, screen->screen_size_width, screen->screen_size_height);
	screen->addr = mlx_get_data_addr(screen->img, &screen->bpp, &screen->line_len, &screen->endian);
}


int	main(int argc, char **argv)
{
	t_game		game;

	init_game(&game);
	check_args(argc, argv);
	if (!parsing_file(argv[1], &game))
		return (free_all(&game), error_msg("Invalid parsing file"), 1);
	ft_init_screen(&game.screen);
	if (!find_player(game.map.big_map, &game))
		return (free_all(&game), error_msg("BUG"), 1);
	raycast(&game, &game.cast);
	mlx_put_image_to_window(game.screen.mlx_ptr, game.screen.win_ptr, game.screen.img, 0, 0);
	mlx_hook(game.screen.win_ptr, KeyPress, KeyPressMask, &keyboard_key, &game);
	mlx_hook(game.screen.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
		&game);
	mlx_loop_hook(game.screen.mlx_ptr, &watching_left_right, &game.dir);
	//mlx_key_hook(game.screen.win_ptr, keyboard_key, &game);
	mlx_hook(game.screen.win_ptr, 17, 0, on_destroy, &game);
	mlx_loop(game.screen.mlx_ptr);
	free_all(&game);
	return (0);
}


//int	main(int argc, char **argv)
//{
//	t_game		game;

//	init_game(&game);
//	check_args(argc, argv);
//	if (!parsing_file(argv[1], &game))
//		return (free_all(&game), error_msg("Invalid parsing file"), 1);
//	ft_init_screen(&game.screen);
//	if (!find_player(game.map.big_map, &game))
//				return (free_all(&game), error_msg("BUG"), 1);
//	raycast(&game, &game.cast);
//	mlx_put_image_to_window(game.screen.mlx_ptr, game.screen.win_ptr, game.screen.img, 0, 0);
//	mlx_hook(game.screen.win_ptr, KeyPress, KeyPressMask, &keyboard_key, &game);
//	mlx_hook(game.screen.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
//		&game);
//	mlx_loop_hook(game.screen.mlx_ptr, &watching_left_right, &game.dir);
//	mlx_hook(game.screen.win_ptr, 17, 0, on_destroy, &game);
//	mlx_loop(game.screen.mlx_ptr);
//	free_all(&game);
//	return (0);
//}
