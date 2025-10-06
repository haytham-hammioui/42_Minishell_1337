/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:06:14 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/04 12:53:13 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	push_cmd_back(t_cmd **head, t_cmd *node)
{
	t_cmd	*tmp;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->fd = malloc(sizeof(t_fd));
	if (!cmd->fd)
		return (free(cmd), NULL);
	cmd->is_cmd_fails = 0;
	cmd->fd->fdin = -1;
	cmd->fd->fdout = -1;
	cmd->fd->pipefd[0] = -1;
	cmd->fd->pipefd[1] = -1;
	cmd->pid = 0;
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = NULL;
	cmd->heredoc_expand = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	append_char_to_str(char c, char **value)
{
	char	tmp[2];
	char	*old;

	tmp[0] = c;
	tmp[1] = '\0';
	old = *value;
	*value = ft_strjoin(old, tmp);
	free(old);
}

char	*merge_strings(char *main_str, char *extra, int free_extra)
{
	char	*joined;

	if (!extra)
		extra = ft_strdup("");
	if (!main_str)
		return (extra);
	joined = ft_strjoin(main_str, extra);
	free(main_str);
	if (free_extra)
		free(extra);
	return (joined);
}
