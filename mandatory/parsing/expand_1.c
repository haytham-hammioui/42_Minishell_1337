/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:13:54 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/01 10:24:53 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*ft_strchr2(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

char	*strjoin_free_c(char *s, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (strjoin_free(s, ft_strdup(str)));
}

char	*get_env_val(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
