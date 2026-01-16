/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:14:46 by skuor             #+#    #+#             */
/*   Updated: 2026/01/16 16:39:39 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parsing_file(const char *path, t_game *game)
{
	int			mode;
	int			fd;
	char		*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	mode = HEADER;
	line = get_next_line(fd);
	while (line)
	{
		if (mode == HEADER)
		{
			if (parse_header(line, &game->config, &mode, game) != 0)
				return (free(line), close(fd), false);
			if (mode == MAP)
			{
				if (parse_map(line, fd, &game->map) != 0 || !validate_map(game))
					return (close(fd), false);
				break ;
			}
			free_and_gnl(&line, fd);
		}
	}
	return (close(fd), true);
}

static int	activate_map_mode(const char *line, t_config *config, int *mode, t_game *game)
{
	if (header_complete(config, game))
	{
		if (is_map_line(line) == false)
			return (1);
		return (*mode = MAP, 0);
	}
	else
		return (1);
}

int	parse_header(const char *line, t_config *config, int *mode, t_game *game)
{
	int	i;
	int	texture;

	if (!line)
		return (1);
	i = skip_ws(line, 0);
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	texture = search_texture(line, i, config);
	if (texture == -1)
		return (1);
	if (texture == 0 || line[i] == 'F' || line[i] == 'C')
	{
		if (line[i] == 'F' || line[i] == 'C')
			if (!parse_color(line, i, game))
				return (1);
		return (*mode = HEADER, 0);
	}
	if (!ft_strchr("10NEWSFC", line[i]))
		return (error_msg("Unknown element in header"), 1);
	return (activate_map_mode(line, config, mode, game));
}

bool	header_complete(t_config *config, t_game *game)
{
	if (!config->no_path)
		return (error_msg("Missing NO path"), false);
	if (!config->so_path)
		return (error_msg("Missing SO path"), false);
	if (!config->we_path)
		return (error_msg("Missing WE path"), false);
	if (!config->ea_path)
		return (error_msg("Missing EA path"), false);
	if (game->floor.r == -1)
		return (error_msg("Missing F color"), false);
	if (game->ceiling.r == -1)
		return (error_msg("Missing C color"), false);
	return (true);
}

bool	is_header_id(char *line)
{
	int	i;

	i = skip_ws(line, 0);
	if (match_id(line, i, "NO"))
		return (true);
	else if (match_id(line, i, "SO"))
		return (true);
	else if (match_id(line, i, "WE"))
		return (true);
	else if (match_id(line, i, "EA"))
		return (true);
	else if (*line == 'F' || *line == 'C')
		return (true);
	return (false);
}
