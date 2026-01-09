/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:44:58 by skuor             #+#    #+#             */
/*   Updated: 2026/01/09 11:22:15 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include "../libft/includes/libft.h"
# include "structs.h"

# define HEADER 0
# define MAP 1
# define DEFAULT "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[92m"



/* ******************************** SOURCES ******************************** */

/* ********* init ********* */
void	init_config(t_config *config);
void	init_tex(t_tex *tex);
void	init_game(t_game *game);
void	init_color(t_color *color);

/* ********* parsing ********* */
int		parse_header(const char *line, t_config *config, int *mode);
bool	parse_color(const char *line, int i, t_config *config);
bool	parsing_file(const char *path, t_game *game);
int		parse_map(char *line, int fd, t_map *map);
bool	is_map_line(const char *line);
bool	check_empty_line_map(char *map);
bool	validate_map(t_game *game);
bool	header_complete(t_config *config);

/* ******************************** UTILS ********************************** */

/* ********* utils ********* */
bool	is_whitespace(char ws);
int		skip_ws(const char *line, int i);
bool	ws_eol(const char *line, int i);
bool	no_digit(char *str);

/* ********* utils parsing ********* */
int		match_id(const char *line, int i, const char *id);
int		extract_path(const char *line, int start, char **path, int *after);
int		count_comma(char *str);

/* ********* free ********* */
void	free_doublechar(char **to_free);
void	free_paths(t_config *config);
void	free_all(t_game *game);

/* ********* error ********* */
void	error_msg(char *msg);
void	error_elem_map(char elem, int line, int col);
void	error_fd(char *path);

#endif
