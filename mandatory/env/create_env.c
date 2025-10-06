/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:49:24 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/04 12:51:54 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_env	*ft_lstnew(char *name, char *value)
{
	t_env	*ptr;

	ptr = malloc(sizeof(t_env));
	if (!ptr)
		return (NULL);
	ptr->value = value;
	ptr->name = name;
	ptr->next = NULL;
	return (ptr);
}

static t_env	*copy_parts0(char *env)
{
	int		j;
	t_env	*menv;
	char	*name;
	char	*value;

	j = 0;
	while (env[j] != '=' && env[j])
		j++;
	name = ft_strndup(env, j);
	if (!name)
		return (NULL);
	if (env[j] != '=')
		return (free(name), NULL);
	value = ft_strdup(env + j + 1);
	if (!value)
		return (free(name), NULL);
	menv = ft_lstnew(name, value);
	if (!menv)
	{
		free(name);
		free(value);
		return (NULL);
	}
	return (menv);
}

int	create_env_if_null(t_env **menv)
{
	t_env	*new_env;

	new_env = ft_lstnew("_", "/usr/bin/env");
	if (!new_env)
		return (ft_lstclear(menv), 0);
	ft_lstadd_back(menv, new_env);
	new_env = ft_lstnew("PWD", getcwd(NULL, 0));
	if (!new_env)
		return (ft_lstclear(menv), 0);
	ft_lstadd_back(menv, new_env);
	return (1);
}

t_env	*create_env(char **env)
{
	int		i;
	t_env	*tmp;
	t_env	*menv;

	i = -1;
	menv = NULL;
	if (!env || !*env)
	{
		if (create_env_if_null(&menv) == 0)
			return (NULL);
		return (menv);
	}
	while (env[++i])
	{
		tmp = copy_parts0(env[i]);
		if (!tmp)
		{
			ft_lstclear(&menv);
			return (NULL);
		}
		ft_lstadd_back(&menv, tmp);
	}
	return (menv);
}
