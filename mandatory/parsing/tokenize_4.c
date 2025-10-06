/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:33:42 by hhammiou          #+#    #+#             */
/*   Updated: 2025/10/04 12:14:19 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	handle_heredoc(t_cmd *cmd, t_token *current, int expand_flag)
{
	cmd->heredoc = append_arg(cmd->heredoc, current->next->value);
	if (current->next)
	{
		if (current->next->was_quoted)
			expand_flag = 0;
		else
			expand_flag = 1;
	}
	cmd->heredoc_expand = append_heredoc_flag(cmd->heredoc_expand, expand_flag);
}

static void	handle_output_redir(t_cmd *cmd, t_token *current)
{
	cmd->outfile = append_arg(cmd->outfile, current->next->value);
	cmd->append = (current->type == TOKEN_APPEND);
}

static void	handle_input_redir(t_cmd *cmd, t_token *current)
{
	cmd->infile = append_arg(cmd->infile, current->next->value);
}

void	process_redirection(t_cmd *cmd, t_token *current)
{
	int	expand_flag;

	expand_flag = 0;
	if (!current->next)
		return ;
	if (current->type == TOKEN_REDIR_IN)
		handle_input_redir(cmd, current);
	else if (current->type == TOKEN_REDIR_OUT || current->type == TOKEN_APPEND)
		handle_output_redir(cmd, current);
	else if (current->type == TOKEN_HEREDOC)
		handle_heredoc(cmd, current, expand_flag);
}

void	append_remaining_text(t_extract_params *params, char **res, int start)
{
	char	*segment;

	if (*params->i > start)
	{
		segment = ft_substr(params->line, start, *params->i - start);
		*res = merge_strings(*res, segment, 1);
	}
}
