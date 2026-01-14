/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:58:43 by skuor             #+#    #+#             */
/*   Updated: 2026/01/14 17:39:24 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map)
{
	map->big_map = NULL;
	map->rows = 0;
	map->cols = 0;
}

void	init_tex(t_tex *tex)
{
	tex->i = 0;
	tex->j = 0;
	tex->start = 0;
	tex->path = NULL;
	tex->fd = 0;
}

void	init_config(t_config *config)
{
	init_color(&config->floor);
	init_color(&config->ceiling);
	config->no_path = NULL;
	config->so_path = NULL;
	config->we_path = NULL;
	config->ea_path = NULL;
}

void	init_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

void	init_parse_map(t_parse_map *p_map)
{
	p_map->map_tmp = ft_strdup("");
	p_map->started = false;
	p_map->end = false;
	p_map->rows = 0;
}
