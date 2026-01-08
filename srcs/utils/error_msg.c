/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:06:11 by skuor             #+#    #+#             */
/*   Updated: 2026/01/08 17:31:15 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(DEFAULT, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	error_elem_map(char elem, int line, int col)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(DEFAULT, 2);
	ft_putstr_fd("Unknown '", 2);
	ft_putchar_fd(elem, 2);
	ft_putstr_fd("' element in map at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(", col ", 2);
	ft_putnbr_fd(col, 2);
	ft_putstr_fd("\n", 2);
}
