/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:50:57 by skuor             #+#    #+#             */
/*   Updated: 2026/01/26 14:35:58 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_time(t_time *time)
{
	time->delta = 0;
	time->last = 0;
}

int	main(int argc, char **argv)
{
	t_game		game;
	int			fd;

	init_game(&game);
	check_args(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (false);
	if (!parsing_file(&game, fd))
		return (free_all(&game), error_msg("Invalid parsing file"), 1);
	ft_init_screen(&game, &game.screen);
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
