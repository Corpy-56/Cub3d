/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 08:57:38 by skuor             #+#    #+#             */
/*   Updated: 2026/01/06 13:22:11 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	can_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("ERROR FD\n");
		return (0);
	}
	close(fd);
	return (1);
}

void	parse_texture(const char *line, const char *id, char **dest)
{
	t_tex	tex;
	int		after;

	init_tex(&tex);
	if (!line)
		return ;
	tex.i = skip_ws(line, 0);
	if (!match_id(line, tex.i, id))
		return ;
	if (*dest)
	{
		ft_printf("error texture\n");
		return ;
	}
	tex.j = tex.i + 2;
	tex.j = skip_ws(line, tex.j);
	if (!extract_path(line, tex.j, &tex.path, &after))
		return ;
	if (!ws_eol(line, after) || !can_open(tex.path))
	{
		free(tex.path);
		return ;
	}
	*dest = tex.path;
}

bool	search_texture(const char *line, int i, t_config *config)
{
	if (match_id(line, i, "NO"))
	{
		ft_printf("MATCH NO\n");
		parse_texture(line, "NO", &config->no_path);
		return (true);
	}
	if (match_id(line, i, "SO"))
	{
		ft_printf("MATCH S0\n");
		parse_texture(line, "SO", &config->so_path);
		return (true);
	}
	if (match_id(line, i, "WE"))
	{
		ft_printf("MATCH WE\n");
		parse_texture(line, "WE", &config->we_path);
		return (true);
	}
	if (match_id(line, i, "EA"))
	{
		ft_printf("MATCH EA\n");
		parse_texture(line, "EA", &config->ea_path);
		return (true);
	}
	return (false);
}

int	parse_header(const char *line, t_config *config, int *mode)
{
	int	i;

	if (!line)
		return (1);
	i = skip_ws(line, 0);
	ft_printf("line[i] = %c\n", line[i]);
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	if (search_texture(line, i, config))
	{
		*mode = HEADER;
		return (0);
	}
	if (line[i] == 'F' || line[i] == 'C')
	{
		if (!parse_color(line, i, config))
		{
			ft_printf("Error : invalid color line\n");
			return (1);
		}
		*mode = HEADER;
		return (0);
	}
	if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'W' || line[i] == 'E' || line[i] == 'S')
	{
		if (is_map_line(line) == false)
			return (ft_printf("Error in map_line\n"), 1);
		ft_printf("mode map activated\n");
		*mode = MAP;
		return (0);
	}
	else 
		return (ft_printf("Error : invalid identifier in header\n"), 1);
	return (0);
}
