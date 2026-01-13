/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:15:39 by skuor             #+#    #+#             */
/*   Updated: 2026/01/13 16:18:17 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	line_is_empty(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = skip_ws(line, 0);
	if (line[i] == '\n' || line[i] == '\0')
		return (true);
	return (false);
}

// bool	one_elem_line(const char *line)
// {
// 	int	i;
// 	int	j;

// 	if (!line)
// 		return (false);
// 	i = skip_ws(line, 0);
// 	if (ft_strchr("NEWS10", line[i]))
// 	{
// 		j = i + 1;
// 		j = skip_ws(line, j);
// 		if (line[j] == '\n' || line[j] == '\0')
// 			return (true);
// 	}
// 	return (false);
// }

bool	invalid_char_map(const char *line)
{
	int		i;
	bool	found_char;

	found_char = false;
	if (!line)
		return (false);
	i = skip_ws(line, 0);
	if (line[i] == '\n' || line[i] == '\0')
		return (false);
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != 'S' && line[i] != ' ')
			return (true);
		i++;
	}
	return (false);
}

bool	is_map_line(const char *line)
{
	int		i;
	bool	found_char;

	found_char = false;
	if (!line)
		return (false);
	i = skip_ws(line, 0);
	if (line[i] == '\n' || line[i] == '\0')
		return (false);
	// if (one_elem_line(line))
	// 	return (error_msg("Line(s) with only one element"), false);
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != 'S' && line[i] != ' ')
			return (error_msg(ERR_MAP), false);
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'W' || line[i] == 'E' || line[i] == 'S')
				found_char = true;
		i++;
	}
	return (found_char);
}
