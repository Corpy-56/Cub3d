/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:48:34 by skuor             #+#    #+#             */
/*   Updated: 2026/01/05 10:36:12 by skuor            ###   ########.fr       */
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
	int		map_height;
	int		map_width;
	int		player_x;
	int		player_y;
}			t_map;

typedef struct s_config
{
	t_map	map;
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