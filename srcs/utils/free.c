/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:50:24 by skuor             #+#    #+#             */
/*   Updated: 2026/01/08 14:00:28 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_doublechar(char **to_free)
{
	int	i;

	i = 0;
	if (to_free == NULL)
		return ;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	free_paths(t_config *config)
{
	if (config->no_path)
	{
		free(config->no_path);
		config->no_path = NULL;
	}
	if (config->so_path)
	{
		free(config->so_path);
		config->so_path = NULL;
	}
	if (config->ea_path)
	{
		free(config->ea_path);
		config->ea_path = NULL;
	}
	if (config->we_path)
	{
		free(config->we_path);
		config->we_path = NULL;
	}
}

void	free_all(t_game *game)
{
	free_paths(&game->config);
	if (game->map.big_map)
	{
		free_doublechar(game->map.big_map);
		game->map.big_map = NULL;
	}
	get_next_line(-1);
}
