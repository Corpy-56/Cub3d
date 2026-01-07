/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:50:57 by skuor             #+#    #+#             */
/*   Updated: 2026/01/07 16:56:22 by agouin           ###   ########.fr       */
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

void	draw_vertical_line(t_config *config, int x, int start, int end, int color)
{
	int y;

	y = start;
	while (y <= end)
	{
		mlx_pixel_put(&config->screen.mlx_ptr, &config->screen.win_ptr, x, y, color);
		y++;
	}
}


void	test_raycast(t_config config)
{
	int i = 0;
	double camera = 0.0;
	double ray_dir_x = 0.0;
	double ray_dir_y = 0.0;
	double side_dist_x = 0.0;
	double side_dist_y = 0.0;
	double delta_dist_x = 0.0;
	double delta_dist_y = 0.0;
	double wall_distance = 0.0;
	int step_x = 0;
	int step_y = 0;
	int draw_start = 0;//debit entre de y dans un x(colonne) donne
	int draw_end = 0;//cest la fin jaffiche une colone
	int hit = 0;
	int side = 0;//mur touche verticalement ou horizontalement
	int map_x = 0;
	int line_height = 0;
	int map_y = 0;

	i = 0;
	line_height = 0;
	camera = 0;
	wall_distance = 0.0;
	draw_start = 0;
	draw_end = 0;
	while(i < config.screen.screen_size_width)
	{
		hit = 0;
		map_x = (int)config.dir.pos_x;
		map_y = (int)config.dir.pos_y;
		camera = 2.0 * i / (double)config.screen.screen_size_width - 1.0;
		ray_dir_x = config.dir.dir_x + config.dir.plan_x * camera;
		ray_dir_y = config.dir.dir_y + config.dir.plan_y * camera;
		delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (config.dir.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - config.dir.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (config.dir.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - config.dir.pos_y) * delta_dist_y;
		}
		while(hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (config.map.big_map[map_x][map_y] > 0)
				hit = 1;
		}
		if (side == 0)
			wall_distance = side_dist_x - delta_dist_x;
		else
			wall_distance = side_dist_y - delta_dist_y;
		//on calcul la hauteur du mur
		line_height = (int)(config.screen.screen_size_height / wall_distance);
		draw_start = -line_height / 2 + config.screen.screen_size_height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + config.screen.screen_size_height / 2;
		if (draw_end >= config.screen.screen_size_height)
			draw_end = config.screen.screen_size_height -1;
		//draw_vertical_line(&config, i, draw_start, draw_end, 0xFFFFFF);
		i++;
	}
	return ;
}


char **test(char **tab)
{
	char **map;
	int i;
	int			fd;

	i = 0;
	map = malloc(10);
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

int	main(int argc, char **argv)
{
	t_config	config;
	int i;

	i = argc;
	//(void)argv;
	//printf("%d\n", argc);
	init_config(&config);
	check_args(i, argv);
	//if (!parsing_file(argv[1], &config))
	//	return (ft_printf("Error parsing file\n"), 1);
	config.map.big_map = test(argv);
	i = 0;
	//while(config.map.big_map[i])
	//{
	//	printf("%s", config.map.big_map[i]);
	//	i++;
	//}
	//ft_init_screen(&config.screen);
	test_raycast(config);
//	mlx_key_hook(config.screen.win_ptr, keyboard_key, &config);
	//mlx_hook(&config.screen.win_ptr, 17, 0, on_destroy, &config);
//	mlx_loop(config.screen.mlx_ptr);
	return (0);
}