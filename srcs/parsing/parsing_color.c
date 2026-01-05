/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:08:46 by skuor             #+#    #+#             */
/*   Updated: 2026/01/05 09:36:14 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_numbers(char *part, int *value)
{
	char	*trimmed;
	int		tmp;

	trimmed = ft_strtrim(part, " \t");
	if (!trimmed)
		return (false);
	if (*trimmed == '\0' || no_digit(trimmed))
	{
		free(trimmed);
		return (false);
	}
	tmp = ft_atoi(trimmed);
	free(trimmed);
	if (tmp < 0 || tmp > 255)
		return (false);
	*value = tmp;
	return (true);
}

bool	parse_3_rgb(char **parts, int *r, int *g, int *b)
{
	if (!parse_numbers(parts[0], r))
		return (false);
	if (!parse_numbers(parts[1], g))
		return (false);
	if (!parse_numbers(parts[2], b))
		return (false);
	return (true);
}

size_t	line_len(const char *line, int start)
{
	size_t	len;

	len = 0;
	while (line[start + len] != '\n' && line[start + len] != '\0')
		len++;
	return (len);
}

bool	parse_rgb_values(const char *line, int i, int *r, int *g, int *b)
{
	size_t	len;
	char	*rgb_str;
	char	**parts;
	int		count;

	len = line_len(line, i);
	rgb_str = ft_substr(line, i, len);
	if (!rgb_str)
		return (false);
	parts = ft_split(rgb_str, ',');
	free(rgb_str);
	if (!parts)
		return (false);
	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
		return (free_doublechar(parts), false);
	if (!parse_3_rgb(parts, r, g, b))
		return (free_doublechar(parts), false);
	free_doublechar(parts);
	return (true);
}

void	set_color(t_config *config, char id, int r, int g, int b)
{
	if (id == 'F')
	{
		config->floor_r = r;
		config->floor_g = g;
		config->floor_b = b;
	}
	else
	{
		config->ceiling_r = r;
		config->ceiling_g = g;
		config->ceiling_b = b;
	}
}

bool	parse_color(const char *line, int i, t_config *config)
{
	char	id;
	int		r;
	int		g;
	int		b;

	id = line[i];
	if (id != 'F' && id != 'C')
		return (false);
	if (id == 'F' && config->floor_r != -1)
		return (false);
	if (id == 'C' && config->ceiling_r != -1)
		return (false);
	i = i + 1;
	i = skip_ws(line, i);
	if (line[i] == '\n' || line[i] == '\0')
		return (false);
	if (!parse_rgb_values(line, i, &r, &g, &b))
		return (false);
	set_color(config, id, r, g, b);
	return (true);
}
