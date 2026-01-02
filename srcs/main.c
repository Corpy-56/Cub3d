/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:50:57 by skuor             #+#    #+#             */
/*   Updated: 2026/01/02 17:29:46 by skuor            ###   ########.fr       */
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
	t_config	config;
	int			mode;
	int			fd;
	char		*line;

	(void)argc;

	init_config(&config);
	mode = HEADER;

	fd = open(argv[1], O_RDONLY);
	// char	*line = "NO ./textures/north.xpm";
	line = get_next_line(fd);
	while (line)
	{
		if (mode == HEADER)
		{
			parse_header_file(line, &config, &mode);
			if (mode == MAP)
			{
				ft_printf("MAP MODE\n");
				return (0);
			}
		}
		else
		{
			ft_printf("MAP MODE\n");
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_printf("config.no_path = %s\n", config.no_path);

	// parse_header_file(line, &config, &mode);

	// if (config.no_path == NULL)
	// 	ft_printf("NO PATH NULL\n");
	// else
	// 	ft_printf("config.no_path = %s\n", config.no_path);
	// ft_printf("mode = %d\n", mode);
}