/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:36:49 by skuor             #+#    #+#             */
/*   Updated: 2025/05/05 11:34:38 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	t;
	char	*d;
	char	*s;

	t = 0;
	d = (char *)dest;
	s = (char *)src;
	if (d == 0 && s == 0)
		return (dest);
	while (t != n)
	{
		d[t] = s[t];
		t++;
	}
	return (dest);
}
