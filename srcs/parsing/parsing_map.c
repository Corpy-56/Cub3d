/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:11:02 by skuor             #+#    #+#             */
/*   Updated: 2026/01/07 16:49:17 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_map(char *line, int fd, t_map *map)
{
	char	*map_tmp;

	if (!line)
		return (1);
	map_tmp = ft_strdup("");
	if (!map_tmp)
		return (free(line), 1);
	while (line)
	{
		map_tmp = ft_strjoin_free(map_tmp, line);
		if (!map_tmp)
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	check_empty_line_map(map_tmp);
	map->big_map = ft_split(map_tmp, '\n');
	free(map_tmp);
	if (!map->big_map || !map->big_map[0])
		return (free_doublechar(map->big_map), 1);
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
			return (ft_printf("Unknown character in map line\n"), false);
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'W' || line[i] == 'E' || line[i] == 'S')
				found_char = true;
		i++;
	}
	return (found_char);
}

void	check_empty_line_map(char *map)
{
	int	i;

	i = 0;
	while (map[i + 1])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
		{
			free(map);
			ft_printf("Error : Empty line(s) in the map\n");
			exit (1);
		}
		if (map[i] == ' ' && map[i + 1] == '\n')
		{
			free(map);
			ft_printf("Error : Empty line(s) in the map\n");
			exit (1);
		}
		i++;
	}
}

int	check_elements(char **map)
{
	int	i;
	int	j;
	int	count_p;


	i = 0;
	count_p = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'W' || map[i][j] == 'S')
				count_p++;
			j++;
		}
	}
	if (count_p != 1)
		return (ft_printf("P = %d\nError : There must be exactly one player\n",
				count_p), 1);
	return (0);
}

int	element_error(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'N' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != 'S' && map[i][j] != '0' && map[i][j] != '1'
				&& map[i][j] != ' ')
				return (ft_printf("Warning : Unknown element in map\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map(t_config *config)
{
	if (element_error(config->map.big_map))
		return (1);
	if (check_elements(config->map.big_map))
		return (1);
	return (0);
}
