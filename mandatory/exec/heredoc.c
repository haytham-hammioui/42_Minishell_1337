/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:06:22 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/06 13:03:20 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	handle_variable_expansion(int fd, char *line, t_env *env, int *i)
{
	char	*vname;
	char	*vvalue;
	int		start;

	start = ++(*i);
	if (line[*i] == '?')
	{
		ft_putnbr(g_exit_code, fd);
		(*i)++;
	}
	else
	{
		while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
			(*i)++;
		vname = ft_substr(line, start, *i - start);
		if (!vname)
			return (0);
		vvalue = get_value(env, vname);
		if (vvalue)
			ft_putstr_fd(vvalue, fd);
		free(vname);
	}
	return (1);
}

static int	expanded_writes(int fd, char *line, t_env *env)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '_'
				|| line[i + 1] == '?' || line[i + 1] == '$'))
		{
			if (!handle_variable_expansion(fd, line, env, &i))
				return (0);
		}
		else
		{
			ft_putchar(line[i], fd);
			i++;
		}
	}
	return (1);
}

char	*expanded_limiter(char *limiter)
{
	int		i;
	int		j;
	char	*new_lim;
	int		len;
	char	quote_char;

	if (!ft_strchr(limiter, '\'') && !ft_strchr(limiter, '\"'))
		return (limiter);
	len = ft_strlen(limiter);
	new_lim = malloc(len + 1);
	i = 0;
	j = 0;
	quote_char = 0;
	while (i < len)
	{
		if ((limiter[i] == '\'' || limiter[i] == '\"') && quote_char == 0)
			quote_char = limiter[i];
		else if (limiter[i] == quote_char)
			quote_char = 0;
		else
			new_lim[j++] = limiter[i];
		i++;
	}
	new_lim[j] = '\0';
	return (new_lim);
}

void	heredoc_handeler(char *limiter, int fd, t_env *env)
{
	char	*line;
	char	*new_line;
	char	*new_lim;

	signal(SIGINT, _here_sig);
	new_lim = expanded_limiter(limiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, new_lim) == 0)
		{
			free(line);
			break ;
		}
		new_line = ft_strjoin(line, "\n");
		if (var(limiter, new_line))
			expanded_writes(fd, new_line, env);
		else
			ft_putstr_fd(new_line, fd);
		free(line);
		free(new_line);
	}
	exit(0);
}

int	here_doc(t_cmd *cmd, char *limiter)
{
	int	status;
	int	fd;

	status = 0;
	signal(SIGQUIT, SIG_IGN);
	fd = create_heredoc(cmd, limiter);
	if (fd == FAILURE)
		return (FAILURE);
	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	if (fd != -1)
		close(fd);
	if (g_exit_code == 1)
		return (FAILURE);
	if (cmd->fd->fdin != -1)
		close(cmd->fd->fdin);
	cmd->fd->fdin = open("/tmp/here_doc", O_RDONLY);
	if (cmd->fd->fdin == -1)
	{
		perror("open");
		return (FAILURE);
	}
	return (SUCCESS);
}
