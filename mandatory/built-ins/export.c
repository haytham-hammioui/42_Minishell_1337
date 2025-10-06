/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:17:40 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/03 15:21:03 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_var_content_exist(t_env *env, t_env *tmp)
{
	t_env	*sc;
	t_env	*ds;
	int		i;

	ds = env;
	sc = tmp;
	i = check_var_content_valid(tmp);
	if (!tmp->name && !tmp->value)
		return (FAILURE);
	if (i == 2 || i == 0)
		return (ft_putstr_fd(" not a valid identifier\n", 2), 3);
	while (ds)
	{
		if (ft_strncmp(ds->name, sc->name, ft_strlen(ds->name) + 1) == 0)
		{
			if (ft_strncmp(ds->value, sc->value, ft_strlen(ds->value) + 1) == 0)
				return (SUCCESS);
			else
				return (2);
		}
		ds = ds->next;
	}
	return (FAILURE);
}

t_env	*copy_parts(char *env)
{
	int		j;
	t_env	*menv;
	char	*name;
	char	*value;

	j = 0;
	if (!env || !*env)
		return (NULL);
	name = NULL;
	value = NULL;
	while (env[j] != '=' && env[j])
		j++;
	name = ft_strndup(env, j);
	if (name == NULL)
	{
		return (NULL);
	}
	if (env[j] == '=' && !env[j + 1])
		value = ft_strdup("");
	else if (env[j] != '\0')
		value = ft_strdup(ft_strchr(env, '='));
	menv = ft_lstnew(name, value);
	if (!menv)
		return (free(name), free(value), NULL);
	return (menv);
}

static t_env	*copy_parts1(char *env)
{
	int		j;
	t_env	*menv;
	char	*name;
	char	*value;

	j = 0;
	if (!env || !*env)
		return (NULL);
	name = NULL;
	value = NULL;
	while (env[j] != '=' && env[j])
		j++;
	name = ft_strndup(env, j);
	if (name == NULL)
	{
		return (NULL);
	}
	if (env[j] == '=' && !env[j + 1])
		value = ft_strdup("");
	else if (env[j] != '\0')
		value = ft_strdup(ft_strchr(env, '='));
	menv = ft_lstnew(name, value);
	if (!menv)
		return (free(name), free(value), NULL);
	return (menv);
}

void	replace_env_var(t_env *tmp, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strncmp(current->name, tmp->name, ft_strlen(current->name)
				+ 1) == 0)
		{
			if (tmp->value)
				free(current->value);
			if (tmp->value)
				current->value = ft_strdup(tmp->value);
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		current = current->next;
	}
}

int	_export(t_cmd *cmd, t_env **env)
{
	int		i[2];
	t_env	*tmp;
	t_env	*menv;

	i[0] = 0;
	i[1] = 1;
	menv = *env;
	if (!cmd->args || !cmd->args[1])
		return (_env(*env, 1), 0);
	while (cmd->args[i[1]])
	{
		tmp = copy_parts1(cmd->args[i[1]++]);
		if (!tmp)
			return (1);
		i[0] = check_var_content_exist(menv, tmp);
		if (i[0] == SUCCESS || i[0] == 3)
			ft_lstclear(&tmp);
		else if (i[0] == FAILURE)
			ft_lstadd_back(&menv, tmp);
		else if (i[0] == 2)
			replace_env_var(tmp, env);
	}
	if (i[0] == 3)
		return (1);
	return (0);
}
