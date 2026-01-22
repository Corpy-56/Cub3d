/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:48:34 by skuor             #+#    #+#             */
/*   Updated: 2026/01/22 13:42:23 by skuor            ###   ########.fr       */
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
	int		bpp;
	void	*img;
	int		line_len;
	int		endian;
	void	*addr;
	//void	
}			t_mlx;

typedef struct s_player
{
	double		pos_row;
	double		pos_col;
	char		spawn_dir;
}			t_player;

typedef struct s_direction
{
	t_player	player;
	double		angle;
	double		rot_speed;
	bool		turn_left;
	bool		turn_right;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
	double		plane_len;
	double		move_speed;
	bool		forward;
	bool		backward;
	bool		strafe_r;
	bool		strafe_l;
	double		dx;
	double		dy;
	double		sx;
	double		sy;
}			t_direction;

typedef struct s_time
{
	double		delta;
	double		last;
}				t_time;

typedef struct s_raycast
{
	double	camera;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_distance;
	int		step_x;
	int		step_y;
	int		draw_start;//debit entre de y dans un x(colonne) donne
	int		draw_end;//cest la fin jaffiche une colone
	int		hit;
	int		side;//mur touche verticalement ou horizontalement
	int		map_x;
	int		line_height;
	int		map_y;
}			t_raycast;

typedef struct s_mini_map
{
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
}			t_mini_map;

typedef struct s_mouse
{
	int		last_x;
	bool	init;
	double	sens;
	bool	lock;
	int		center_x;
	int		center_y;
}		t_mouse;

typedef struct s_map
{
	char	**big_map;
	int		rows;
	int		cols;
}			t_map;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_parse_map
{
	char	*map_tmp;
	bool	started;
	bool	end;
	int		fd;
	int		rows;
	int		total_chars;
}			t_parse_map;

typedef struct s_ext
{
	int		new_rows;
	int		new_cols;
	int		x;
	int		y;
}			t_ext;

typedef struct s_flood
{
	char	**map;
	int		rows;
	int		cols;
	bool	open;
}			t_flood;

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}			t_config;

typedef struct s_game
{
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	t_mlx		screen;
	t_direction	dir;
	t_raycast	cast;
	t_mini_map	mini;
	t_config	config;
	t_color		color;
	t_player	player;
	t_mouse		mouse;
	t_time		time;
}			t_game;

#endif