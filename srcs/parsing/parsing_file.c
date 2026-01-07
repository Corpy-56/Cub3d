/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:14:46 by skuor             #+#    #+#             */
/*   Updated: 2026/01/07 16:48:09 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parsing_file(const char *path, t_config *config)
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
			if (parse_header(line, config, &mode) != 0)
				return (free(line), close(fd), false);
			if (mode == MAP)
			{
				if (parse_map(line, fd, &config->map) != 0)
					return (close(fd), false);
				if (validate_map(config))
					return (close(fd), false);
				break ;
			}
			free(line);
			line = get_next_line(fd);
		}
		else
		{
			if (parse_map(line, fd, &config->map) != 0)
				return (close(fd), false);
			break ;
		}
	}
	close(fd);
	return (true);
}
