/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:50:57 by skuor             #+#    #+#             */
/*   Updated: 2026/01/22 16:31:10 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_hook(game.screen.win_ptr, KeyPress, KeyPressMask, &keyboard_key, &game);
	mlx_hook(game.screen.win_ptr, KeyRelease, KeyReleaseMask,
		&handle_keyrelease, &game);
	mlx_loop_hook(game.screen.mlx_ptr, &player_movement, &game);
	mlx_hook(game.screen.win_ptr, 17, 0, on_destroy, &game);
	mlx_loop(game.screen.mlx_ptr);
	return (0);
}
