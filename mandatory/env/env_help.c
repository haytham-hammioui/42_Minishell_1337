/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:56:02 by hhammiou          #+#    #+#             */
/*   Updated: 2025/10/04 13:15:54 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_env	*find_env_var(t_env *env_list, const char *name)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					s;
	unsigned long long	r;

	i = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	r = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
		if (r > LLONG_MAX && s > 0)
			return (-1);
		if (r > LLONG_MAX && s < 0)
			return (0);
	}
	return ((int)(r * s));
}

void	increment_shlvl(t_env **env)
{
	int		shlvl;
	char	*new_value;
	t_env	*shlvl_node;

	if (!env)
		(*env)->is_env_fails = 1;
	if (!env)
		return ;
	shlvl_node = find_env_var(*env, "SHLVL");
	if (!shlvl_node)
	{
		ft_lstadd_back(env, ft_lstnew(ft_strdup("SHLVL"), ft_strdup("1")));
		return ;
	}
	shlvl = ft_atoi(shlvl_node->value);
	shlvl++;
	if (shlvl > 1000)
		shlvl = 1;
	else if (shlvl < 0)
		shlvl = 0;
	new_value = ft_itoa(shlvl);
	if (!new_value)
		return ;
	free(shlvl_node->value);
	shlvl_node->value = new_value;
}
