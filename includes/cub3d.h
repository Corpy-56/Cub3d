/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:44:58 by skuor             #+#    #+#             */
/*   Updated: 2026/01/02 17:28:56 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../libft/includes/libft.h"
#include "structs.h"

# define HEADER 0
# define MAP 1

/* ******************************** SOURCES ******************************** */

/* ********* init ********* */
void	init_config(t_config *config);
void	init_tex(t_tex *tex);

/* ********* parsing ********* */
void	parse_header_file(const char *line, t_config *config, int *mode);
bool	parse_color(const char *line, int i, t_config *config);

/* ******************************** UTILS ********************************** */

/* ********* utils ********* */
bool	is_whitespace(char ws);
int		skip_ws(const char *line, int i);
bool	ws_eol(const char *line, int i);
bool	no_digit(char *str);

/* ********* utils parsing ********* */
int		match_id(const char *line, int i, const char *id);
int		extract_path(const char *line, int start, char **path, int *after);

/* ********* free ********* */
void	free_doublechar(char **to_free);


#endif
