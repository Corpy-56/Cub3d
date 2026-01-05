/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 08:57:38 by skuor             #+#    #+#             */
/*   Updated: 2026/01/05 09:36:43 by skuor            ###   ########.fr       */
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

	tex.path = NULL;
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
		parse_texture(line, "SO", &config->so_path);
		return (true);
	}
	if (match_id(line, i, "WE"))
	{
		parse_texture(line, "WE", &config->we_path);
		return (true);
	}
	if (match_id(line, i, "EA"))
	{
		parse_texture(line, "EA", &config->ea_path);
		return (true);
	}
	return (false);
}

void	parse_header(const char *line, t_config *config, int *mode)
{
	int	i;

	if (!line)
		return ;
	i = skip_ws(line, 0);
	ft_printf("i = %d\nline[i] = %c\n", i, line[i]);
	if (line[i] == '\n' || line[i] == '\0')
		return ;
	if (search_texture(line, i, config))
	{
		*mode = HEADER;
		return ;
	}
	if (line[i] == 'F' || line[i] == 'C')
	{
		if (!parse_color(line, i, config))
		{
			ft_printf("Error : invalid color line\n");
			return ;
		}
		*mode = HEADER;
		return ;
	}
	if (line[i] == '1' || line[i] == '0')
	{
		*mode = MAP;
		return ;
	}
	ft_printf("Error : invalid identifier in header\n");
	return ;
}
