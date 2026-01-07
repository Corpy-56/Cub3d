/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:48:34 by skuor             #+#    #+#             */
/*   Updated: 2026/01/07 16:19:40 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_tex
{
	int		i;
	int		j;
	int		start;
	char	*path;
	int		fd;
}			t_tex;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		screen_size_width;
	int		screen_size_height;
}			t_mlx;

typedef struct s_direction
{
	//char	**big_map;
	//int		map_height;
	//int		map_width;
	double		pos_x;
	double		pos_y;//position
	double		dir_x;
	double		dir_y;//ou il regarde
	double		plan_x;
	double		plan_y;//largeur de la camera FOV
}			t_direction;

typedef struct s_map
{
	char	**big_map;
	int		map_height;
	int		map_width;
	int		player_x;
	int		player_y;
}			t_map;

typedef struct s_config
{
	t_map	map;
	t_mlx	screen;
	t_direction	dir;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
}			t_config;

typedef struct s_game
{
	t_config	*config;
	const char	*line;
	int			*mode;
}			t_game;

#endif