/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:50:57 by agouin             #+#    #+#             */
/*   Updated: 2026/01/05 14:44:57 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(int i, t_config *game, char *string)
{
	(void)game;

	//if (game != NULL && i != 9 && i != 6)
	//	ft_free_struct(game);
	if (i == 6)
	{
		write(2, "Error\nProblem with Assets\n", 27);
	//	on_destroy(game);
	}
	write(2, string, ft_strlen(string));
	exit (1);
}

int	ft_find_point(char *temp, int k)
{
	int	j;

	j = 0;
	while (temp[j++] != '\0')
	{
		if (temp[j] == '.')
			k++;
		if (temp[j] == '/' && k > 0)
			k--;
	}
	return (k);
}

int	check_cub(char *temp, int i)
{
	int		fd;
	char	buf;
	int		k;

	k = 0;
	if (i <= 4)
		return (ft_error(0, NULL, "Error : Map file extension must be .cub\n"));
	fd = open(temp, O_RDONLY);
	if (fd == -1)
		return (ft_error(0, NULL, "Fd failed - Bad file\n"));
	if (read(fd, &buf, 1) < 0)
	{
		close(fd);
		return (ft_error(4, NULL, "Argument is not a file\n"));
	}
	close(fd);
	k = ft_find_point(temp, k);
	if (temp[i - 1] == 'b' && temp[i - 2] == 'u'
		&& temp[i - 3] == 'c' && temp[i - 4] == '.'
		&& (temp[i - 5] != '/' && temp[i - 5] != '\0') && k == 1)
		return (0);
	return (ft_error(0, NULL, "Error : Map file extension must be .cub\n"));
}

int	check_args(int argc, char **argv)
{
	if (argc > 2)
		ft_error(0, NULL, "Error : Too many arguments !\n");
	if (argc < 2)
		ft_error(0, NULL, "Error : No map file !\n");
	check_cub(argv[1], ft_strlen(argv[1]));
	return (0);
}
