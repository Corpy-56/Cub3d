/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:11:02 by skuor             #+#    #+#             */
/*   Updated: 2026/01/09 16:43:35 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	line_is_empty(char *line)
{
	int	i;

	i = skip_ws(line, 0);
	if (line[i] == '\n' || line[i] == '\0')
		return (true);
	return (false);
}

int	parse_map(char *line, int fd, t_map *map)
{
	char	*map_tmp;
	bool	started;
	bool	end;

	started = false;
	end = false;
	if (!line)
		return (1);
	map_tmp = ft_strdup("");
	if (!map_tmp)
		return (free(line), 1);
	while (line)
	{
		if (line_is_empty(line))
		{
			if (started)
				end = true;
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_map_line(line))
		{
			if (end)
			{
				(free(line), free(map_tmp));
				return (error_msg("Empty line(s) in map"), 1);
			}
			started = true;
			map_tmp = ft_strjoin_free(map_tmp, line);
			if (!map_tmp)
				return (free(line), 1);
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (started)
		{
			if (invalid_char_map(line))
			{
				if (end)
				{
					(free(line), free(map_tmp));
					return (error_msg("Map must be last"), 1);
				}
				else
				{
					(free(line), free(map_tmp));
					return (error_msg("Unknown element in map"), 1);
				}
			}
		}
		(free(line), free(map_tmp));
		return (error_msg("Invalid map"), 1);
	}
	if (check_empty_line_map(map_tmp) == false)
		return (1);
	map->big_map = ft_split(map_tmp, '\n');
	free(map_tmp);
	if (!map->big_map || !map->big_map[0])
		return (free_doublechar(map->big_map), 1);
	ft_print_map(map->big_map);
	return (0);
}

 // permet de verifier qu'on est bien dans une map -> si ok on passe en mode map
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
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != 'S' && line[i] != ' ')
			return (false);
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'W' || line[i] == 'E' || line[i] == 'S')
				found_char = true;
		i++;
	}
	return (found_char);
}

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

bool	validate_map(t_game *game)
{
	if (check_elements(game->map.big_map))
		return (false);
	ft_printf(GREEN"Valid map !\n"DEFAULT);
	return (true);
}
