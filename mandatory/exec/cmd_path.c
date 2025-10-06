/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:24:09 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/02 14:51:04 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_env	*get_path(t_env *env)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->name, "PATH", ft_strlen("PATH")))
			return (tmp_env);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **myenv)
{
	int		i;
	char	*temp;
	char	*cmds;
	char	*full_path;

	i = -1;
	if (!ft_strncmp(cmd, "\0", 1))
		return (NULL);
	cmds = ft_strdup(cmd);
	if (!cmds)
		return (NULL);
	while (myenv[++i])
	{
		temp = ft_strjoin("/", cmds);
		if (!temp)
			return (free(cmds), NULL);
		full_path = ft_strjoin(myenv[i], temp);
		free(temp);
		if (!full_path)
			return (free(cmds), NULL);
		if (access(full_path, X_OK) != -1)
			return (free(cmds), full_path);
		free(full_path);
	}
	return (free(cmds), NULL);
}

void	find_me(t_cmd *curr, t_env *path, char **paths)
{
	while (curr)
	{
		if (!curr->args || !curr->cmd)
		{
			curr = curr->next;
			continue ;
		}
		if ((!ft_strncmp("./", curr->args[0], 2) || ft_strchr(curr->args[0],
					'/')))
			;
		else if (path && check_built_in(curr))
		{
			free(curr->cmd);
			curr->cmd = find_path(curr->args[0], paths);
		}
		else if (!check_built_in(curr) && ft_strncmp(curr->args[0], "env", 4))
		{
			free(curr->cmd);
			curr->cmd = ft_strdup(curr->args[0]);
		}
		curr = curr->next;
	}
}

int	cmd_find_path(t_cmd *cmd)
{
	t_env	*path;
	t_cmd	*curr;
	char	**paths;

	if (!cmd || !cmd->env || !cmd->or_env || !cmd->args || !cmd->args[0])
		return (FAILURE);
	curr = cmd;
	paths = NULL;
	path = get_path(curr->env);
	if (path && path->value)
		paths = ft_split_n(path->value, ':');
	find_me(curr, path, paths);
	cmd->is_path_works = 0;
	if (path && path->value && paths)
	{
		while (cmd)
		{
			cmd->is_path_works = 1;
			cmd = cmd->next;
		}
		free_str(paths);
	}
	return (SUCCESS);
}
