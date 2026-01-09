/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:35:03 by skuor             #+#    #+#             */
/*   Updated: 2026/01/09 12:26:37 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	match_id(const char *line, int i, const char *id)
{
	if (line[i] == id[0] && line[i + 1] == id[1])
		if (is_whitespace(line[i + 2]))
			return (1);
	return (0);
}

int	extract_path(const char *line, int start, char **path, int *after)
{
	int	i;

	if (!line || !after || !path)
		return (0);
	*path = NULL;
	start = skip_ws(line, start);
	if (line[start] == '\0' || line[start] == '\n')
		return (error_msg("Path not found"), 0);
	i = start;
	while (!is_whitespace(line[i]) && line[i] != '\n' && line[i] != '\0')
		i++;
	*path = ft_substr(line, start, i - start);
	if (*path == NULL)
		return (0);
	*after = i;
	return (1);
}

int	count_comma(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

bool	can_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (error_fd(path), false);
	close(fd);
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
