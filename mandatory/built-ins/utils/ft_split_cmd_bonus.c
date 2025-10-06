/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:10:29 by smaksiss          #+#    #+#             */
/*   Updated: 2025/09/09 10:55:49 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	ft_count_words(const char *s, size_t i, int c)
{
	size_t	count;
	size_t	flag;

	flag = 1;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			while (s[++i] != '\'' && s[i])
				if (s[i] == '\'')
					break ;
			count++;
		}
		else if (s[i] != c && flag)
		{
			count++;
			flag = 0;
		}
		else if (s[i] == c)
			flag = 1;
		i++;
	}
	return (count);
}

static size_t	ft_word_len(char const *s, int c)
{
	size_t	i;

	i = 0;
	if (s[i] != '\'')
		while (s[i] != c && s[i])
			i++;
	else
		while (s[++i] != '\'' && s[i])
			if (s[i + 1] == '\'' || s[i + 1] == ':')
				break ;
	return (i);
}

int	ft_is_not(char *ptr)
{
	size_t	k;

	k = 0;
	while (ptr[k])
	{
		if (ptr[k] == '\'')
			return (1);
	}
	return (0);
}

static char	**ft_cpyn(const char *s, char c, char **ptr)
{
	size_t	i;
	int		k;
	size_t	word_len;

	i = 0;
	k = 0;
	while (s[i] && k < ft_count_words(s, 0, c))
	{
		while (s[i] == ' ' && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		if (s[i] == ':')
			i++;
		word_len = ft_word_len(&s[i], c);
		if (s[i] == '\'')
			i++;
		ptr[k] = ft_substr(s, i, word_len);
		if (!ptr[k])
			return (NULL);
		i += word_len;
		k++;
	}
	ptr[k] = NULL;
	return (ptr);
}

char	**ft_split_n(char const *s, char c)
{
	char	**ptr;
	size_t	word;

	if (s == NULL)
		return (NULL);
	word = ft_count_words(s, 0, c);
	ptr = malloc(sizeof(char *) * (ft_count_words(s, 0, c) + 1));
	if (!ptr)
		return (FAILURE);
	if (word == 0)
	{
		ptr[0] = NULL;
		return (ptr);
	}
	if (!ptr)
		return (NULL);
	ptr = ft_cpyn(s, c, ptr);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}
