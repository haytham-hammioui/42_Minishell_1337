/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:14:19 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/02 16:09:47 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	count_valid_minus_n(char **tmp)
{
	int		i;
	int		j;
	char	**help;

	i = 0;
	help = tmp;
	if (!help || !help[0])
		return (-1);
	while (help[i])
	{
		j = 0;
		if (help[i][j] != '-')
			return (i);
		j++;
		while (help[i][j] != '\0')
		{
			if (help[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	if (help[i] == NULL)
		return (i);
	return (-1);
}

int	get_minus_n_count(t_cmd *cmd)
{
	int	k;

	if (!cmd || !cmd->args[1])
		return (-1);
	k = count_valid_minus_n(&cmd->args[1]);
	if (cmd->args[1][0] != '-')
		return (-1);
	return (k - 1);
}

void	print_with_nl(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
	}
	ft_putstr_fd("\n", 1);
}

int	_echo(t_cmd *cmd)
{
	int	i;

	if (!cmd->args || !cmd->args[1] || !cmd->args[1][0])
		return (ft_putstr_fd("\n", 1), 0);
	i = get_minus_n_count(cmd);
	if (i == -1)
		print_with_nl(cmd->args);
	else
	{
		i++;
		while (cmd->args[++i])
		{
			ft_putstr_fd(cmd->args[i], 1);
			if (cmd->args[i + 1])
				ft_putstr_fd(" ", 1);
		}
	}
	return (0);
}
