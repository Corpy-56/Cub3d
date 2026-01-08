/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:50:57 by skuor             #+#    #+#             */
/*   Updated: 2026/01/08 16:47:09 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_args(int argc, char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (argc > 2)
	{
		ft_printf("Error : Too many arguments !\n");
		exit (1);
	}
	if (argc < 2)
	{
		ft_printf("Error : No map file !\n");
		exit (1);
	}
	if (!ft_strnstr(&argv[1][len - 4], ".cub", 4))
	{
		ft_printf("Error : Map file extension must be .cub\n");
		exit (1);
	}
	return (0);
}

// int main(int argc, char **argv)
// {
// 	t_game	game;

// 	check_args(argc, argv);
// 	parse_header_file(game.line, game.config, game.mode);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
		return (1);
	init_game(&game);
	if (!parsing_file(argv[1], &game))
		return (free_all(&game), error_msg("Invalid parsing file"), 1);
	free_all(&game);

	return (0);

}
