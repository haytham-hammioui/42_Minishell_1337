/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:05:33 by hhammiou          #+#    #+#             */
/*   Updated: 2025/10/04 10:37:10 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	process_token(t_cmd **cmd, t_cmd **cmds, t_token *token, 
		int *skip_next)
{
	if (token->type == TOKEN_WORD)
	{
		if (!(*cmd)->cmd && token->value && token->value[0] != '\0')
			(*cmd)->cmd = ft_strdup(token->value);
		(*cmd)->args = append_arg((*cmd)->args, token->value);
	}
	else if (token->type == TOKEN_PIPE)
	{
		push_cmd_back(cmds, *cmd);
		*cmd = init_cmd();
	}
	else
	{
		process_redirection(*cmd, token);
		*skip_next = 1;
	}
}

void	parse_tokens(t_token *tokens, t_cmd **cmds)
{
	t_cmd	*cmd;
	t_token	*token;
	int		skip_next;

	skip_next = 0;
	cmd = init_cmd();
	token = tokens;
	if (!cmd)
		return ;
	while (token)
	{
		if (skip_next)
		{
			skip_next = 0;
			token = token->next;
			continue ;
		}
		process_token(&cmd, cmds, token, &skip_next);
		token = token->next;
	}
	if (cmd->cmd || cmd->args || cmd->infile || cmd->outfile || cmd->heredoc)
		push_cmd_back(cmds, cmd);
	else
		return (free(cmd->fd), free(cmd));
}

t_cmd	*tokenizer(char *line, t_env *env)
{
	t_cmd	*cmds;
	t_token	*tokens;
	int		i;

	cmds = NULL;
	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (ft_strchr(" \t", line[i]))
			i++;
		else
			add_token(line, &i, env, &tokens);
	}
	parse_tokens(tokens, &cmds);
	free_tokens(&tokens);
	return (cmds);
}

void	expand_var(char *line, int *i, t_env *env, char **res)
{
	if (line[*i] && line[*i + 1] == '?')
	{
		(*i) += 2;
		*res = merge_strings(*res, ft_itoa(g_exit_code), 1);
		if (line[*i] && line[*i + 1] == '|')
			g_exit_code = 0;
		return ;
	}
	(*i)++;
	if (ft_isdigit(line[*i]))
	{
		(*i)++;
		g_exit_code = 0;
		return ;
	}
	read_env_name(line, i, env, res);
}
