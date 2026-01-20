/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:44:58 by skuor             #+#    #+#             */
/*   Updated: 2026/01/20 15:29:24 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/time.h>

# include "structs.h"
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"

# define HEADER 0
# define MAP 1
# define DEFAULT "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[92m"

# define PI 3.141592653589793
# define FOV 1.15

# define ERR_EMPTY "Empty line(s) in map"
# define ERR_LAST "Map must be the last element"
# define ERR_ELEM "Unknown element in map"
# define ERR_MAP "Invalid map"

/* ******************************** SOURCES ******************************** */

int		on_destroy(t_game *game);

/* ********* init ********* */
// void	init_map(t_direction *dir, t_map * map);
void	init_config(t_config *config, t_game *game);
void	init_tex(t_tex *tex);
void	ft_init_ray(t_raycast *cast, t_mini_map *mini);
void	init_game(t_game *game);
void	init_color(t_color *color);
void	init_parse_map(t_parse_map *p_map);
void	init_border(t_ext *ext, int rows, int cols);
void	init_flood(t_flood *flood, t_map *map);
void	init_dir(t_direction *dir);

/* ******************************* PLAYER ********************************* */

/* ********* position ********* */
int		find_player(char **map, t_game *game);
double	convert_angle(char orientation);

/* ********* movement ********* */
int		watching_left_right(void *dir);
void	calc_dir_plan(t_direction *dir);

/* ********* handle input ********* */
int		handle_keyrelease(int keycode, t_game *game);
int		keyboard_key(int keycode, t_game *game);

/* ******************************* PARSING ********************************* */

/* ********* file & header ********* */
bool	parsing_file(const char *path, t_game *game);
int		parse_header(const char *line, t_config *config, int *mode, t_game *game);
bool	header_complete(t_config *config, t_game *game);
bool	is_header_id(char *line);

/* ********* texture ********* */
bool	parse_texture(const char *line, const char *id, char **dest);
int		search_texture(const char *line, int i, t_config *config);

/* ********* color ********* */
bool	parse_color(const char *line, int i, t_game *game);
bool	parse_numbers(char *part, int *value);
bool	parse_3_rgb(char **parts, int *r, int *g, int *b);
bool	parse_rgb_values(const char *line, int i, t_color *color);
void	set_color(t_game *game, char id, t_color color);

/* ********* map ********* */
int		parse_map(char *line, int fd, t_map *map);
bool	is_map_line(const char *line);
bool	validate_map(t_game *game);

/* ********* map checks ********* */
int		check_elements(char **map);
bool	line_is_empty(char *line);
bool	one_elem_line(const char *line);
bool	invalid_char_map(const char *line);

/* ********* map grid ********* */
char	**normalize_map(t_map *map);

/* ********* flood fill ********* */
void	flood_fill(t_flood *f, int y, int x);
void	fill_space(char **map);
bool	check_closed_map(t_game *game);

/* ********* parsing ********* */
int		check_args(int argc, char **argv);
int		check_cub(char *temp, int i);
int		ft_find_point(char *temp, int k);
int		ft_error(int i, t_config *game, char *string);

/* ********* raycast ********* */
void	raycast(t_game *game, t_raycast *cast);
void	hit_wall_boucle(t_raycast *cast, t_game *game);
void	wall_height_calcul(t_raycast *cast, t_mlx *screen);
void	radius_calcul(t_raycast *cast, t_direction *dir, t_player *player);
void	calcul_delta_dist(t_raycast *cast, t_player *player);
void	draw_vertical_line(t_config *config, int x, int start, int end, int color); //il faut lenlever
void 	draw_mini_map(t_map *map, t_mlx *screen, t_player *play);
void	draw_wall_column(t_raycast *cast, t_mlx *screen, t_mini_map *mini, int x);
void	ft_print_mini_map(t_raycast *cast, t_mlx *screen, t_mini_map *mini, int x, int y);
void	my_mlx_pixel_put(t_mlx *screen, int x, int y, int color);



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

/* ********* utils map ********* */
void	map_size(t_map *map);
int		ft_min(int a, int b);
int		check_size_map(char *line, t_parse_map *p);

/* ********* free ********* */
void	free_doublechar(char **to_free);
void	free_paths(t_config *config);
void	free_all(t_game *game);
void	free_and_err(char *line, char *map_tmp, char *msg);
void	free_and_gnl(char **line, int fd);
void	free_rows(char **grid, int i);

/* ********* error ********* */
void	error_msg(char *msg);
void	error_elem_map(char elem, int line, int col);
void	error_fd(char *path);
void	error_texture(char *dest);
void	error_nb_player(int nb_player);


#endif
