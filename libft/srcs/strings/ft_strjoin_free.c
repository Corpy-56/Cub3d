/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:22:27 by skuor             #+#    #+#             */
/*   Updated: 2026/01/05 16:38:16 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*str;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = ft_malloc(len1 + len2 + 1);
	if (!str)
		return (free(s1), NULL);
	if (s1)
		ft_memcpy(str, s1, len1);
	if (s2)
		ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	free(s1);
	return (str);
}

// char	*ft_strjoin_free(char const *s1, char const *s2)
// {
// 	char	*str;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (s1 == NULL && s2 == NULL)
// 		return (0);
// 	str = ft_calloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1), 1);
// 	if (!str)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		str[i + j] = s2[j];
// 		j++;
// 	}
// 	str[i + j] = '\0';
// 	free((char *)s1);
// 	return (str);
// }
