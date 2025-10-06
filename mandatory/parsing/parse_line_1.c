/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:32:36 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/03 16:24:15 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_redirect(char *line)
{
	int		i;
	char	red_type;
	char	in_quote;

	i = 0;
	in_quote = 0;
	while (line[i])
	{
		if (!in_quote && (line[i] == '"' || line[i] == '\''))
			in_quote = line[i];
		else if (in_quote && line[i] == in_quote)
			in_quote = 0;
		if (!in_quote && (line[i] == '>' || line[i] == '<'))
		{
			red_type = line[i];
			if (check_redirect_syntax(line, &i, red_type))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ambiguous_realfunc(char *value)
{
	int	i;
	int	flag;
	int	words;

	i = -1;
	flag = 0;
	words = 0;
	if (!value || !*value)
		return (1);
	while (value[++i])
	{
		if (value[i] == ' ')
			flag = 0;
		else if (!flag)
		{
			flag = 1;
			words += 1;
		}
	}
	return (words > 1);
}

int	check_ambiguity(char *line, int *i, t_env *env)
{
	char	key[100];
	char	*value;
	int		j;

	j = 0;
	(*i)++;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_')
		&& j < (int)(sizeof(key) - 1))
		key[j++] = line[(*i)++];
	key[j] = '\0';
	value = get_value(env, key);
	return (ambiguous_realfunc(value));
}

static int	check_redir_ambiguity(char *line, int *i, t_env *env)
{
	if (*i > 0 && line[*i - 1] != ' ' && line[*i - 1] != '\t'
		&& line[*i - 1] != '>' && line[*i - 1] != '<')
		return (0);
	if (line[*i + 1] && line[*i + 1] != ' ' && line[*i + 1] != '\t'
		&& line[*i + 1] != '>' && line[*i + 1] != '<')
		return (0);
	if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
		(*i)++;
	(*i)++;
	if (!line[*i])
		return (0);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (!line[*i])
		return (0);
	if (line[*i] == '$' && check_ambiguity(line, i, env))
		return (1);
	return (0);
}

int	ambiguous_red(char *line, t_env *env)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (line[++i])
	{
		if ((line[i] == '"' || line[i] == '\''))
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		if (!quote && (line[i] == '>' || line[i] == '<'))
		{
			if (check_redir_ambiguity(line, &i, env))
				return (1);
		}
	}
	return (0);
}
