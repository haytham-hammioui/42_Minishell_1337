/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:27:32 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/03 22:38:41 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_num_valid(char *str, int c)
{
	int	i;
	int	is_neg;

	i = 0;
	is_neg = 1;
	while (str[i] <= ' ' && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			is_neg = -1;
	}
	if (!ft_isdigit(str[i]))
		return (FAILURE);
	if (!str[i] || str[i] < '0' || str[i] > '9')
		return (FAILURE);
	while (str[i] == '0' && str[i])
		i++;
	while (str[i++] && str[i] >= '0' && str[i] <= '9')
		c++;
	if ((c >= 20 && !str[i] && is_neg == 1) || c > 20 || str[i])
		return (FAILURE);
	if (c == 20 && !str[i] && is_neg == 1)
		return (FAILURE);
	return (SUCCESS);
}

int	is_llong_valid(char *s)
{
	int		i;
	char	*max;

	i = 0;
	while (s[i] <= 32 && s[i])
		i++;
	if (s[i] == '-')
		max = "-9223372036854775808";
	else
		max = "9223372036854775807";
	while (i < 20 && s[i])
	{
		if (s[i] > *max)
			return (FAILURE);
		if (s[i] < *max)
			return (SUCCESS);
		i++;
		max++;
	}
	return (SUCCESS);
}

int	is_valid_args(t_cmd *cmd)
{
	if (!cmd->args[1])
		return (g_exit_code);
	if (is_num_valid(cmd->args[1], 0) == FAILURE)
		return (g_exit_code = 255, 255);
	if (is_llong_valid(cmd->args[1]) == FAILURE)
		return (g_exit_code = 255, 255);
	if (cmd->args[2] && cmd->args[2][0])
		return (FAILURE);
	return (SUCCESS);
}

long long	convert_to_ll(char *str)
{
	int			i;
	long long	is_neg;
	long long	res;

	i = 0;
	res = 0;
	is_neg = 1;
	while (str[i] <= 32 && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			is_neg = -1;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * is_neg);
}

int	f_exit(t_cmd *cmd)
{
	long long	i;

	i = is_valid_args(cmd);
	ft_putstr_fd("exit\n", 1);
	if (cmd->args[1] && cmd->args[2])
	{
		perror("too many arguments");
		return (1);
	}
	if (i == 255)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->args[0], 1);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(i);
	}
	else if (cmd->args[0] && cmd->args[1])
		i = convert_to_ll(cmd->args[1]);
	exit(i);
	return (i);
}
