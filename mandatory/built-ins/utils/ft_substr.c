/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:32:07 by smaksiss          #+#    #+#             */
/*   Updated: 2025/09/17 12:15:01 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	i = 0;
	if (!dst || !*dst || !src || !*src)
		return (-1);
	slen = ft_strlen(src);
	if (dstsize == 0)
		return (slen);
	while (*src && i < dstsize - 1)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (slen);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	if (str && *str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}
