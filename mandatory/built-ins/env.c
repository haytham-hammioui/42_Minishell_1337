/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:03:35 by smaksiss          #+#    #+#             */
/*   Updated: 2025/09/20 11:27:23 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	_env_export(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (1);
	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		if (!tmp->value)
			;
		else if (tmp->value && tmp->value[0] == '=' && tmp->value[0] == '=')
			ft_putstr_fd("=\"\"", 1);
		else
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	_env(t_env *env, int i)
{
	t_env	*tmp;

	if (!env)
		return (0);
	tmp = env;
	if (i == 1)
		return (_env_export(env), 1);
	while (tmp)
	{
		if (tmp->next && tmp->next->next && !tmp->value)
			tmp = tmp->next;
		else if (!tmp->next && !tmp->value)
			break ;
		if (tmp->name && tmp->value)
		{
			ft_putstr_fd(tmp->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
