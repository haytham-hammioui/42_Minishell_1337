/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:07:53 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/03 16:23:41 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*get_env_value(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	env_replace1(t_env **menv, char *name, char *value)
{
	t_env	*env;

	env = *menv;
	while (env)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			if (!env->value)
				return (FAILURE);
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}

int	oldpwd_replace_with_value(t_env **menv, char *value)
{
	return (env_replace1(menv, "OLDPWD", value));
}

int	_cd_cases(t_cmd *cmd, t_env **menv, char **path, int *is_free)
{
	if (!cmd->args || !cmd->args[1] || ft_strncmp(cmd->args[1], "$HOME",
			6) == 0)
	{
		*path = get_env_value(*menv, "HOME");
		if (!*path)
			return (ft_putstr_fd("cd: HOME not set\n", 2), FAILURE);
	}
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		*path = get_env_value(*menv, "OLDPWD");
		if (!*path)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), FAILURE);
	}
	else if (ft_strncmp(cmd->args[1], ".", 2) == 0)
	{
		*is_free = 1;
		*path = getcwd(NULL, 0);
		if (!*path)
			return (perror("cd: error getting current directory"), FAILURE);
	}
	else
		*path = cmd->args[1];
	return (SUCCESS);
}

int	_cd(t_cmd *cmd, t_env **menv)
{
	char	*path;
	char	old_cwd[PATH_MAX];
	int		is_free;

	path = NULL;
	is_free = 0;
	if (!getcwd(old_cwd, sizeof(old_cwd)))
		return (ft_putstr_fd("cd: error getting current directory\n", 2), 1);
	if (_cd_cases(cmd, menv, &path, &is_free) != SUCCESS)
		return (1);
	if (access(path, F_OK) == -1)
		return (ft_putstr_fd("cd: No such file or directory\n", 2), 1);
	if (chdir(path) == -1)
		return (ft_putstr_fd("cd: cannot change directory\n", 2), 1);
	if (oldpwd_replace_with_value(menv, old_cwd) != SUCCESS)
		return (ft_putstr_fd("cd: failed to update OLDPWD\n", 2), 1);
	if (pwd_replace(menv) != SUCCESS)
		return (ft_putstr_fd("cd: failed to update PWD\n", 2), 1);
	if (is_free == 1)
		free(path);
	return (0);
}
