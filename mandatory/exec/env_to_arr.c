/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:45:57 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/02 14:57:13 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_env_len(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	if (!env)
		return (0);
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**env_to_arr(t_env *env)
{
	t_env	*tmp;
	char	*tmp_val;
	char	**ret_env;
	int		i;

	tmp = env;
	i = 0;
	ret_env = malloc(sizeof(char *) * (ft_env_len(env) + 1));
	if (!ret_env || !env)
		return (NULL);
	while (tmp)
	{
		tmp_val = ft_strjoin(tmp->name, "=");
		if (!tmp_val)
			return (ret_env[i + 1] = NULL, free_str(ret_env), NULL);
		ret_env[i] = ft_strjoin(tmp_val, tmp->value);
		free(tmp_val);
		if (!ret_env[i])
			return (ret_env[i + 1] = NULL, free_str(ret_env), NULL);
		i++;
		tmp = tmp->next;
	}
	ret_env[i] = NULL;
	return (ret_env);
}
