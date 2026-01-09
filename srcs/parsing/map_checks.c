/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:15:39 by skuor             #+#    #+#             */
/*   Updated: 2026/01/09 15:20:35 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

    // if started:
    //     free(line)
    //     free(map_tmp)
    //     error_msg("Map must be last / content after map")
    //     return (1)

    // // cas théorique: parse_map appelée alors qu'on n'est pas sur une map
    // free(line)
    // free(map_tmp)
    // error_msg("Invalid map")
    // return (1)

bool	check_empty_line_map(char *map)
{
	int	i;

	i = 0;
	while (map[i + 1])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
		{
			free(map);
			error_msg("Empty line(s) in the map");
			return (false);
		}
		if (map[i] == ' ' && map[i + 1] == '\n')
		{
			free(map);
			error_msg("Empty line(s) in the map");
			return (false);
		}
		i++;
	}
	return (true);
}

int	check_elements(char **map)
{
	int	i;
	int	j;
	int	count_p;

	i = 0;
	count_p = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("NEWS01 ", map[i][j]))
				return (error_elem_map(map[i][j], i, j), 1);
			if (ft_strchr("NEWS", map[i][j]))
				count_p++;
			j++;
		}
		i++;
	}
	if (count_p != 1)
		return (error_nb_player(count_p), 1);
	return (0);
}

