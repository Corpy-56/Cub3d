/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:44:58 by skuor             #+#    #+#             */
/*   Updated: 2026/01/09 16:25:11 by skuor            ###   ########.fr       */
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

/* ******************************* PARSING ********************************* */

/* ********* file ********* */
bool	parsing_file(const char *path, t_game *game);
int		parse_header(const char *line, t_config *config, int *mode);
bool	header_complete(t_config *config);
bool	is_header_id(char *line);

/* ********* texture ********* */
bool	parse_texture(const char *line, const char *id, char **dest);
int		search_texture(const char *line, int i, t_config *config);

/* ********* color ********* */
bool	parse_color(const char *line, int i, t_config *config);
bool	parse_numbers(char *part, int *value);
bool	parse_3_rgb(char **parts, int *r, int *g, int *b);
bool	parse_rgb_values(const char *line, int i, t_color *color);
void	set_color(t_config *config, char id, t_color color);

/* ********* map ********* */
int		parse_map(char *line, int fd, t_map *map);
bool	is_map_line(const char *line);
bool	validate_map(t_game *game);
bool	invalid_char_map(const char *line);

/* ********* map checks ********* */
bool	check_empty_line_map(char *map);
int		check_elements(char **map);
bool	check_end_map(char *map);


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
bool	can_open(char *path);
size_t	line_len(const char *line, int start);

/* ********* free ********* */
void	free_doublechar(char **to_free);
void	free_paths(t_config *config);
void	free_all(t_game *game);

/* ********* error ********* */
void	error_msg(char *msg);
void	error_elem_map(char elem, int line, int col);
void	error_fd(char *path);
void	error_texture(char *dest);
void	error_nb_player(int nb_player);


#endif
