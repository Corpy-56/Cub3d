/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:14:46 by skuor             #+#    #+#             */
/*   Updated: 2026/01/07 16:39:10 by agouin           ###   ########.fr       */
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
			parse_header(line, config, &mode);
			if (mode == MAP)
				parse_map(line, fd, config->map);
		}
		else
		{
			ft_printf("MAP MODE\n");
			free(line);
			close (fd);
			return (true);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_printf("config.no_path = %s\n", config->no_path);
	return (true);

	// parse_header(line, &config, &mode);

	// if (config.no_path == NULL)
	// 	ft_printf("NO PATH NULL\n");
	// else
	// 	ft_printf("config.no_path = %s\n", config.no_path);
	// ft_printf("mode = %d\n", mode);
}
