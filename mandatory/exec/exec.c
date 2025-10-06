/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:02:41 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/04 14:35:29 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	close_child(t_cmd *cmd)
{
	if (cmd->fd->fdin != -1)
		close(cmd->fd->fdin);
	if (cmd->next)
	{
		close(cmd->fd->pipefd[1]);
		cmd->next->fd->fdin = cmd->fd->pipefd[0];
	}
}

int	exec_builtin_handle(t_cmd *cmds)
{
	int	in_org;
	int	out_org;

	if (cmds->infile && cmds->fd->fdin == -1)
		return (g_exit_code = FAILURE, FAILURE);
	in_org = dup(STDIN_FILENO);
	out_org = dup(STDOUT_FILENO);
	if (cmds->outfile)
		if (dup_stdout(cmds->fd, cmds->fd->fdout) == FAILURE)
			return (g_exit_code = FAILURE, FAILURE);
	exec_built_in(cmds, &cmds->env);
	if (dup_stdin(cmds->fd, in_org) == FAILURE)
		return (g_exit_code = FAILURE, FAILURE);
	if (dup_stdout(cmds->fd, out_org) == FAILURE)
		return (g_exit_code = FAILURE, FAILURE);
	if (in_org != -1)
		close(in_org);
	if (out_org != -1)
		close(out_org);
	if (cmds->fd->fdin != STDIN_FILENO)
		close(cmds->fd->fdin);
	if (cmds->fd->fdout != STDOUT_FILENO)
		close(cmds->fd->fdout);
	return (SUCCESS);
}

int	here_doc_open_fds(t_cmd *cmds)
{
	int	i;

	i = 0;
	if (cmds->heredoc)
	{
		while (cmds->heredoc[i])
		{
			if (here_doc(cmds, cmds->heredoc[i]) == FAILURE)
			{
				if (g_exit_code == 1)
					return (FAILURE);
				else
					return (g_exit_code = 1, perror("here_doc"), FAILURE);
			}
			i++;
		}
	}
	if (open_fds(cmds) == FAILURE)
	{
		g_exit_code = 1;
		return (FAILURE);
	}
	if (!cmds->args || !cmds->args[0])
		close_fds(cmds->fd);
	return (SUCCESS);
}

void	exec_cmd_logic(t_cmd *current, int is_first)
{
	if (here_doc_open_fds(current) == FAILURE)
	{
		close_child(current);
		return ;
	}
	if (current->args && !check_built_in(current) && !current->next
		&& !is_first && !ft_strncmp("env", current->cmd, 4)
		&& current->env->is_env_fails)
		exec_builtin_handle(current);
	else if (current->args && is_first == 0
		&& !ft_strncmp("exit", current->args[0], 5) && !current->next)
		g_exit_code = main_exit(current);
	else if (!current->is_path_works && current->cmd 
		&& !ft_strncmp("env", current->cmd, 4))
		exec_cmd(current);
	else if (current->args && !check_built_in(current) && !current->next
		&& !is_first && ft_strncmp("env", current->cmd, 4))
		exec_builtin_handle(current);
	else if (current->args && current->args[0])
	{
		if (exec_cmd(current) == FAILURE)
			return ;
	}
}

void	exec(t_cmd *cmds)
{
	t_cmd	*current;
	int		is_first;

	current = cmds;
	is_first = 0;
	cmd_find_path(current);
	while (current)
	{
		exec_cmd_logic(current, is_first);
		current = current->next;
		is_first++;
	}
	wait_children(cmds);
	intial_signals();
}
