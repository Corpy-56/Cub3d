/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 08:57:38 by skuor             #+#    #+#             */
/*   Updated: 2026/01/09 16:24:18 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		return (error_texture(*dest), false);
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



