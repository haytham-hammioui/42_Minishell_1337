/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_fds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:58:43 by hhammiou          #+#    #+#             */
/*   Updated: 2025/10/04 12:58:46 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	o_in(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->infile[i])
	{
		cmd->fd->fdin = open(cmd->infile[i], O_RDONLY);
		if (cmd->fd->fdin < 0)
		{
			perror("infile");
			return (FAILURE);
		}
		if (cmd->infile[i + 1])
			close(cmd->fd->fdout);
		i++;
	}
	return (SUCCESS);
}

int	o_out(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->outfile[i])
	{
		if (cmd->append)
			cmd->fd->fdout = open(cmd->outfile[i],
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			cmd->fd->fdout = open(cmd->outfile[i], O_WRONLY | O_TRUNC | O_CREAT,
					0644);
		if (cmd->fd->fdout == -1)
		{
			perror("fds error");
			if (cmd->fd->fdin != -1)
				close(cmd->fd->fdin);
			return (FAILURE);
		}
		if (cmd->outfile[i + 1])
			close(cmd->fd->fdout);
		i++;
	}
	return (SUCCESS);
}

int	open_fds(t_cmd *cmd)
{
	if (cmd->next)
		if (pipe(cmd->fd->pipefd) == -1)
			return (perror("pipe"), FAILURE);
	if (cmd->outfile && cmd->outfile[0])
		if (o_out(cmd) == FAILURE)
			return (FAILURE);
	if (cmd->infile && cmd->infile[0])
		if (o_in(cmd) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

int	dup_stdout(t_fd *fd, int newfd)
{
	if (newfd == -1)
		return (FAILURE);
	if (dup2(newfd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close_fds(fd);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	dup_stdin(t_fd *fd, int newfd)
{
	if (newfd == -1)
		return (FAILURE);
	if (dup2(newfd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close_fds(fd);
		return (FAILURE);
	}
	return (SUCCESS);
}
