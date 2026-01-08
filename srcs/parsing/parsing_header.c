/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 08:57:38 by skuor             #+#    #+#             */
/*   Updated: 2026/01/08 16:50:54 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	can_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("ERROR FD : %s\n", path);
		return (false);
	}
	close(fd);
	return (true);
}

bool	parse_texture(const char *line, const char *id, char **dest)
{
	t_tex	tex;
	int		after;

	init_tex(&tex);
	if (!line)
		return (false);
	tex.i = skip_ws(line, 0);
	if (!match_id(line, tex.i, id))
		return (false);
	if (*dest)
	{
		ft_printf("Error : %s already loaded\n", *dest);
		return (false);
	}
	tex.j = tex.i + 2;
	tex.j = skip_ws(line, tex.j);
	if (!extract_path(line, tex.j, &tex.path, &after))
		return (false);
	if (!ws_eol(line, after) || !can_open(tex.path))
	{
		free(tex.path);
		return (false);
	}
	*dest = tex.path;
	return (true);
}

int	search_texture(const char *line, int i, t_config *config)
{
	if (match_id(line, i, "NO"))
	{
		if (parse_texture(line, "NO", &config->no_path) == false)
			return (-1);
		return (0);
	}
	if (match_id(line, i, "SO"))
	{
		if (parse_texture(line, "SO", &config->so_path) == false)
			return (-1);
		return (0);
	}
	if (match_id(line, i, "WE"))
	{
		if (parse_texture(line, "WE", &config->we_path) == false)
			return (-1);
		return (0);
	}
	if (match_id(line, i, "EA"))
	{
		if (parse_texture(line, "EA", &config->ea_path) == false)
			return (-1);
		return (0);
	}
	return (1);
}

int	parse_header(const char *line, t_config *config, int *mode)
{
	int	i;
	int	texture;

	if (!line)
		return (1);
	i = skip_ws(line, 0);
	// ft_printf("line[i] = %c\n", line[i]); // a retirer
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	texture = search_texture(line, i, config);
	if (texture == -1)
		return (1);
	else if (texture == 0)
	{
		*mode = HEADER;
		return (0);
	}
	if (line[i] == 'F' || line[i] == 'C')
	{
		if (!parse_color(line, i, config))
			return (1);
		*mode = HEADER;
		return (0);
	}
	if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
		&& line[i] != 'W' && line[i] != 'E' && line[i] != 'S'
		&& line[i] != 'F' && line[i] != 'C')
		return (ft_printf("Unknown '%c' element in header\n", line[i]), 1);
	if (header_complete(config))
	{
		if (is_map_line(line) == false)
			return (1);
		ft_printf("mode map activated\n"); // a retirer
		*mode = MAP;
		return (0);
	}
	else
		return (1);
	return (0);
}

bool	header_complete(t_config *config)
{
	if (!config->no_path)
		return (error_msg("Missing NO path"), false);
	if (!config->so_path)
		return (error_msg("Missing SO path"), false);
	if (!config->we_path)
		return (error_msg("Missing WE path"), false);
	if (!config->ea_path)
		return (error_msg("Missing EA path"), false);
	if (config->floor.r == -1)
		return (error_msg("Missing F color"), false);
	if (config->ceiling.r == -1)
		return (error_msg("Missing C color"), false);
	return (true);
}
