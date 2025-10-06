/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:33:05 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/03 16:26:54 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_and(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = strlen(line);
	while (i < len && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (i < len && line[i] == '&')
		return (1);
	while (i < len)
	{
		if (line[i] == '&' && i + 1 < len && line[i + 1] == '&')
			return (1);
		i++;
	}
	return (0);
}

int	handle_quote_char(char *line, int *i, int *open)
{
	if (*open == 0 && (line[*i] == '\"' || line[*i] == '\''))
	{
		if (line[*i] == '\'')
			*open = 1;
		else
			*open = 2;
		(*i)++;
		return (1);
	}
	else if ((*open == 2 && line[*i] == '\"') || (*open == 1
			&& line[*i] == '\''))
	{
		(*i)++;
		*open = 0;
		return (1);
	}
	return (0);
}

t_cmd	*parse_line(t_minishell *mshell)
{
	mshell->cmds = NULL;
	if (mshell->line)
		add_history(mshell->line);
	mshell->cmds = NULL;
	if (check_quotes_and(mshell->line))
		return (g_exit_code = 258, write(2, "syntax error near unexpected\n",
				30), NULL);
	if (check_pipe(mshell->line))
		return (g_exit_code = 258, write(2,
				"syntax error near unexpected token\n", 36), NULL);
	if (ambiguous_red(mshell->line, mshell->new_env))
		return (g_exit_code = 258, write(2, "ambiguous redirect\n", 19), NULL);
	if (check_redirect(mshell->line))
		return (g_exit_code = 258, write(2,
				"syntax error near unexpected token\n", 36), NULL);
	mshell->cmds = tokenizer(mshell->line, mshell->new_env);
	return (mshell->cmds);
}

int	check_redirect_syntax(char *line, int *i, char red_type)
{
	if (line[*i + 1] == red_type)
		(*i)++;
	(*i)++;
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	if (!line[*i] || line[*i] == '>' || line[*i] == '<' || line[*i] == '|')
		return (1);
	if (check_filename(&line[*i]))
		return (1);
	return (0);
}

char	*get_value(t_env *env, char *key)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (curr->name && key && ft_strcmp(curr->name, key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
