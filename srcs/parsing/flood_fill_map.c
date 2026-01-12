/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:35:04 by skuor             #+#    #+#             */
/*   Updated: 2026/01/12 12:36:05 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



bool	validate_map(t_game *game)
{
	if (check_elements(game->map.big_map))
		return (false);
	ft_printf(GREEN"Valid map !\n"DEFAULT);
	return (true);
}
