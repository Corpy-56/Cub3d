/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:58:43 by skuor             #+#    #+#             */
/*   Updated: 2026/01/07 16:35:50 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config(t_config *config)
{
	config->no_path = NULL;
	config->so_path = NULL;
	config->we_path = NULL;
	config->ea_path = NULL;
	config->floor_r = -1;
	config->floor_g = -1;
	config->floor_b = -1;
	config->ceiling_r = -1;
	config->ceiling_g = -1;
	config->ceiling_b = -1;
	config->dir.pos_x = 22.0;//peut etre changer en fonction de la map
	config->dir.pos_y = 12.0;
	config->dir.dir_x = -1.0;//il faut changer ca en fonction de la map cest ou il regarde
	config->dir.dir_y = 0.0;
	config->dir.plan_x = 0.0;
	config->dir.plan_y = 0.66;
	//config->map = NULL;
	//config->map_height = 0;
	//config->map_width = 0;
	//config->player_x = -1;
	//config->player_y = -1;
}

void	init_tex(t_tex *tex)
{
	tex->i = 0;
	tex->j = 0;
	tex->start = 0;
	tex->path = NULL;
	tex->fd = 0;
}