/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:11:02 by skuor             #+#    #+#             */
/*   Updated: 2026/01/14 17:43:58 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_empty_line(char **line, t_parse_map *p)
{
	if (p->started)
		p->end = true;
	free_and_gnl(line, p->fd);
	return (0);
}

static int	handle_mapline(char **line, t_parse_map *p)
{
	if (p->end)
		return (free_and_err(*line, p->map_tmp, ERR_EMPTY), 1);
	p->started = true;
	if (check_size_map(*line, p))
		return (free(*line), free(p->map_tmp), 1);
	p->map_tmp = ft_strjoin_free(p->map_tmp, *line);
	if (!p->map_tmp)
		return (free(*line), 1);
	p->rows++;
	free_and_gnl(line, p->fd);
	return (0);
}

static int	handle_invalid_line(char **line, t_parse_map *p)
{
	if (p->started && invalid_char_map(*line))
	{
		if (p->end)
			return (free_and_err(*line, p->map_tmp, ERR_LAST), 1);
		return (free_and_err(*line, p->map_tmp, ERR_ELEM), 1);
	}
	return (free_and_err(*line, p->map_tmp, ERR_MAP), 1);
}

static int	handle_line(char **line, t_parse_map *p)
{
	if (line_is_empty(*line))
		return (handle_empty_line(line, p));
	if (is_map_line(*line))
		return (handle_mapline(line, p));
	return (handle_invalid_line(line, p));
}

int	parse_map(char *line, int fd, t_map *map)
{
	t_parse_map	p;

	init_parse_map(&p);
	p.fd = fd;
	if (!line)
		return (1);
	if (!p.map_tmp)
		return (free(line), 1);
	while (line)
	{
		if (handle_line(&line, &p))
			return (1);
	}
	map->big_map = ft_split(p.map_tmp, '\n');
	free(p.map_tmp);
	if (!map->big_map || !map->big_map[0])
		return (free_doublechar(map->big_map), 1);
	map_size(map);
	return (0);
}

