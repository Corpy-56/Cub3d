/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:48:34 by skuor             #+#    #+#             */
/*   Updated: 2026/01/14 14:01:25 by agouin           ###   ########.fr       */
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
	int	bpp;
	void	*img;
	int	line_len;
	int endian;
	void *addr;
	//void	
}			t_mlx;

typedef struct s_direction
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
}			t_direction;

typedef struct s_raycast
{
	double	camera;
	double	ray_dir_x;
	double ray_dir_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double wall_distance;
	int step_x;
	int step_y;
	int draw_start;//debit entre de y dans un x(colonne) donne
	int draw_end;//cest la fin jaffiche une colone
	int hit;
	int side;//mur touche verticalement ou horizontalement
	int map_x;
	int line_height;
	int map_y;
}			t_raycast;


typedef struct s_map
{
	char	**big_map;
	int		map_height;
	int		map_width;
	int		player_x;
	int		player_y;
}			t_map;

typedef struct s_mini_map
{
	int start_x;
	int end_x;
	int start_y;
	int	end_y;
}			t_mini_map;

typedef struct s_config
{
	t_map	map;
	t_mlx	screen;
	t_direction	dir;
	t_raycast cast;
	t_mini_map	mini;
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