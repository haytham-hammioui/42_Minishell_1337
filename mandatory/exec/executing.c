/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:36:51 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/04 14:49:06 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_command_path_errors(t_cmd *cmd)
{
	DIR	*dir;

	if (!cmd->cmd || !ft_strncmp(cmd->args[0], "..", 4))
		return (0);
	dir = opendir(cmd->cmd);
	if (dir && ft_strchr(cmd->cmd, '/'))
		return (closedir(dir), perror("is a directory"), exit(126), 1);
	else if (dir)
		closedir(dir);
	else if (ft_strchr(cmd->cmd, '/') && access(cmd->cmd, F_OK) == -1)
		return (perror("Permission denied"), exit(127), 1);
	else if (ft_strchr(cmd->cmd, '/') && access(cmd->cmd, X_OK) == -1)
		return (perror("No such file or directory"), exit(126), 1);
	return (0);
}

void	setup_command_redirections(t_cmd *cmd, t_fd *fd)
{
	if (cmd->fd->fdin >= 0)
	{
		if (dup_stdin(fd, cmd->fd->fdin) == FAILURE)
			cleanup_and_exit(cmd, FAILURE);
		if (cmd->fd->fdin != STDIN_FILENO)
			close(cmd->fd->fdin);
	}
	if (cmd->outfile)
	{
		if (dup_stdout(fd, cmd->fd->fdout) == FAILURE)
			cleanup_and_exit(cmd, FAILURE);
		if (cmd->fd->fdout != STDOUT_FILENO)
			close(cmd->fd->fdout);
	}
	else if (cmd->next)
	{
		if (dup_stdout(fd, cmd->fd->pipefd[1]) == FAILURE)
			cleanup_and_exit(cmd, FAILURE);
		close(cmd->fd->pipefd[1]);
	}
	if (cmd->fd->pipefd[0] >= 0 && cmd->fd->pipefd[0] != cmd->fd->fdin
		&& cmd->fd->pipefd[0] != STDIN_FILENO)
		close(cmd->fd->pipefd[0]);
}

int	is_valid_command_name(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !*cmd)
		return (0);
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

void	execute_child(t_cmd *cmd)
{
	intial_signals();
	setup_command_redirections(cmd, cmd->fd);
	check_command_path_errors(cmd);
	if (!ft_strncmp("env", cmd->cmd, 4) && !cmd->is_path_works)
	{
		ft_putstr_fd("env: No such file or directory\n", 2);
		cleanup_and_exit(cmd, 127);
	}
	else if (!check_built_in(cmd))
	{
		g_exit_code = exec_builtin_handle(cmd);
		cleanup_and_exit(cmd, g_exit_code);
	}
	else if (!cmd->cmd || !is_valid_command_name(cmd->args[0])
		|| !ft_strcmp(cmd->args[0], ".."))
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_exit_code = 127;
		cleanup_and_exit(cmd, 127);
	}
	close(cmd->fd->pipefd[0]);
	execve(cmd->cmd, cmd->args, cmd->or_env);
	perror("execve");
	cleanup_and_exit(cmd, 127);
}

int	exec_cmd(t_cmd *cmd)
{
	signal(SIGINT, SIG_IGN);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"), close_fds(cmd->fd), FAILURE);
	else if (cmd->pid == 0)
		execute_child(cmd);
	else
		close_child(cmd);
	return (SUCCESS);
}
