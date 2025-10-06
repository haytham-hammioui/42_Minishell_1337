/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:22:02 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/02 15:20:15 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd()");
		return (1);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	return (0);
}

int	pwd_replace(t_env **menv)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		return (FAILURE);
	return (env_replace1(menv, "PWD", cwd));
}

int	check_var_content_valid(t_env *tmp)
{
	int	i;

	i = 0;
	if (ft_isalpha(tmp->name[0]) == 0 && tmp->name[0] != '_')
		return (2);
	while (tmp->name[i])
	{
		if (ft_isalnum(tmp->name[i]) == 0 && tmp->name[i] != '_')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
