/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:50:57 by skuor             #+#    #+#             */
/*   Updated: 2026/01/14 14:07:42 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_destroy(t_config *game)
{
	//free_image(game);
	mlx_destroy_window(game->screen.mlx_ptr, game->screen.win_ptr);
	//mlx_destroy_display(game->screen.mlx_ptr);
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

void	ft_init_screen(t_mlx *screen, t_config *config)
{
	//char	*relative_path = "wall.xpm";
	//void	*img
	(void)config;
	//int width;
	//int height;

//	width = 1;
//	height = 1;
	screen->mlx_ptr = mlx_init();
	if (screen->mlx_ptr == NULL)
		ft_error(0, NULL, "Mlx_init failed\n");
	//mlx_get_screen_size(screen->mlx_ptr, &screen->screen_size_width,
	//	&screen->screen_size_height);
	screen->screen_size_width = 1920;
	screen->screen_size_height = 1080;
	screen->win_ptr = mlx_new_window(screen->mlx_ptr, screen->screen_size_width, screen->screen_size_height, "Cub3d");
	screen->img = mlx_new_image(config->screen.mlx_ptr, config->screen.screen_size_width, config->screen.screen_size_height);
	screen->addr = mlx_get_data_addr(screen->img, &screen->bpp, &screen->line_len, &screen->endian);
//	printf("bpp=%d | line_len=%d | endian=%d\n", screen->bpp, screen->line_len, screen->endian);
		//img = mlx_xpm_file_to_image(screen->mlx_ptr, relative_path, &screen->screen_size_width, &screen->screen_size_height);
	//screen->image_wall = mlx_xpm_file_to_image(screen->mlx_ptr, "star.xpm",
	//		&width, &height);
	//if (!screen->image_wall)
	//	ft_error(0, config, "nul\n");
}
void	my_mlx_pixel_put1(t_config *config, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= config->screen.screen_size_width || y >= config->screen.screen_size_height)
		return;
	dst = config->screen.addr + (y * config->screen.line_len + x * (config->screen.bpp / 8));
	*(unsigned int *)dst = color;
}

//void	draw_vertical_line(t_config *config, int x, int start, int end, int color)
//{
//	int y;

//	y = start;
//	//config->screen.image_wall = mlx_get_data_addr(config->screen.image_wall, &config->screen.bpp, &config->screen.line_len, &config->screen.endian);
//	while (y <= end)
//	{
//		//my_mlx_pixel_put(config, x, y, color);
//		//mlx_pixel_put(config->screen.mlx_ptr, config->screen.win_ptr, x, y, color);
//		//mlx_put_image_to_window(config->screen.mlx_ptr, config->screen.win_ptr, config->screen.image_wall,
//		//	x * 1, y * 1);
//		my_mlx_pixel_put(config, x, y, color);
//		y++;
//	}
//}



char **test(char **tab)
{
	char **map;
	int i;
	int			fd;

	i = 0;
	map = malloc(20);
	fd = open(tab[1], O_RDONLY);
	if (fd == -1)
		return (NULL);
	//map[i] = get_next_line(fd);
	while ((map[i] = get_next_line(fd)) != NULL)
	{
	//	map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
	//ft_printf("config.no_path = %s\n", config->no_path);
	map[i] = NULL;
	return (map);
}

void	clear_image(t_config *config)
{
	ft_bzero(config->screen.addr, config->screen.line_len * config->screen.screen_size_height);
}

int	main(int argc, char **argv)
{
	t_config	config;
	int i;

	i = argc;
	init_config(&config);
	check_args(i, argv);
	//if (!parsing_file(argv[1], &config))
	//	return (ft_printf("Error parsing file\n"), 1);
	config.map.big_map = test(argv);
	ft_init_screen(&config.screen, &config);
	//clear_image(&config);
	raycast(&config);
	//my_mlx_pixel_put1(&config, 100, 101, 0xFF0000);
	//my_mlx_pixel_put1(&config, 100, 102, 0xFF0000);
	//my_mlx_pixel_put1(&config, 100, 103, 0xFF0000);
	//my_mlx_pixel_put1(&config, 100, 104, 0xFF0000);
	mlx_put_image_to_window(config.screen.mlx_ptr, config.screen.win_ptr, config.screen.img, 0, 0);
	mlx_key_hook(config.screen.win_ptr, keyboard_key, &config);
	mlx_hook(config.screen.win_ptr, 17, 0, on_destroy, &config);
	mlx_loop(config.screen.mlx_ptr);
	return (0);
}
