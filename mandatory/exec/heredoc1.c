/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 09:47:05 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/01 13:05:46 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	create_heredoc(t_cmd *cmd, char *limiter)
{
	int	fd;

	if (access("/tmp/here_doc", F_OK) == 0)
		unlink("/tmp/here_doc");
	fd = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
		return (perror("open"), FAILURE);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (close(fd), perror("fork"), FAILURE);
	if (cmd->pid == 0)
		heredoc_handeler(limiter, fd, cmd->env);
	return (fd);
}

void	_here_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
	exit(1);
}

int	var(char *limiter, char *line)
{
	int	i;

	i = 0;
	if (ft_strchr(limiter, '\'') || ft_strchr(limiter, '\"'))
		return (0);
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (line[i + 1] && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'
					|| line[i + 1] == '?'))
				return (1);
		}
		i++;
	}
	return (0);
}
