/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:55:24 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/03 22:38:52 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	cleanup_and_exit(t_cmd *cmd, int flag)
{
	close_fds(cmd->fd);
	if (flag == 127)
		g_exit_code = flag;
	else
		flag = g_exit_code;
	exit(flag);
}

int	main_exit(t_cmd *cmd)
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
		ft_putstr_fd("exit: ", 1);
		ft_putstr_fd(cmd->args[0], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(i);
	}
	else if (cmd->args[0] && cmd->args[1])
		i = convert_to_ll(cmd->args[1]);
	f_clean(cmd);
	exit(i);
	return (i);
}

int	check_built_in(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		return (0);
	return (-1);
}

int	exec_built_in(t_cmd *cmd, t_env **env)
{
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		return (g_exit_code = _echo(cmd));
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		return (g_exit_code = _cd(cmd, env));
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		return (g_exit_code = _pwd());
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		return (g_exit_code = _env(*env, 0));
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		return (g_exit_code = _export(cmd, env));
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		return (g_exit_code = _unset(cmd, env));
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		return (f_exit(cmd));
	return (FAILURE);
}
