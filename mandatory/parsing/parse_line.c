/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:31:03 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/02 11:00:28 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_quotes_and(char *line)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i])
	{
		if (i > 0 && line[i - 1] == '\\')
			i++;
		else if (handle_quote_char(line, &i, &open))
			continue ;
		else
			i++;
	}
	if (check_and(line))
		return (1);
	return (open);
}

int	check_semicolon(char *line)
{
	int		i;
	char	q;

	i = -1;
	q = 0;
	while (line[++i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if (!q)
				q = line[i];
			else if (q == line[i])
				q = 0;
		}
		else if (!q && line[i] == ';')
			return (1);
	}
	return (0);
}

static int	check_pipe_syntax(char *line, int i)
{
	int	j;

	if (line[i] != '|')
		return (0);
	j = i + 1;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] == '\0')
		return (1);
	if (line[j] == '|')
		return (1);
	return (0);
}

int	check_pipe(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '|')
		return (1);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if (!quote)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		if (!quote && check_pipe_syntax(line, i))
			return (1);
		i++;
	}
	if (check_semicolon(line))
		return (1);
	return (0);
}

int	check_filename(char *line)
{
	int	i;
	int	start;

	i = 0;
	if (line[i] == '"' || line[i] == '\'')
		i++;
	start = i;
	if (line[i] == '"' || line[i] == '\'')
		return (0);
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '<'
		&& line[i] != '>' && line[i] != '|' && line[i] != '"'
		&& line[i] != '\'')
		i++;
	if (i == start)
	{
		if ((line[0] == '"' && line[1] == '"') || (line[0] == '\''
				&& line[1] == '\''))
			return (0);
		return (1);
	}
	return (0);
}
