/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:48:34 by skuor             #+#    #+#             */
/*   Updated: 2026/01/13 15:09:35 by skuor            ###   ########.fr       */
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

typedef struct s_map
{
	char	**big_map;
	int		rows;
	int		cols;
	int		player_x;
	int		player_y;
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
	t_map	map;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	t_color	floor;
	t_color	ceiling;
}			t_config;

typedef struct s_game
{
	t_config	config;
	t_map		map;
	t_color		color;
}			t_game;




#endif