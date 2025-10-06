/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:50:21 by hhammiou          #+#    #+#             */
/*   Updated: 2025/10/03 19:52:33 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	process_quoted_content(t_extract_params *params, char **res,
		int *start)
{
	char	*segment;

	while (params->line[*params->i] 
		&& params->line[*params->i] != params->quote)
	{
		if (params->quote == '"' && params->line[*params->i] == '$' 
			&& (ft_isalnum(params->line[*params->i + 1])
				|| params->line[*params->i + 1] == '_' 
				|| params->line[*params->i + 1] == '?'))
		{
			if (*params->i > *start)
			{
				segment = ft_substr(params->line, *start, *params->i - *start);
				*res = merge_strings(*res, segment, 1);
			}
			expand_var(params->line, params->i, params->env, res);
			*start = *params->i;
		}
		else
			(*params->i)++;
	}
}

char	*extract_quoted_text(t_extract_params *params)
{
	char	*res;
	int		start;

	res = ft_strdup("");
	start = ++(*params->i);
	if (params->was_quoted)
		*params->was_quoted = 1;
	process_quoted_content(params, &res, &start);
	append_remaining_text(params, &res, start);
	if (params->line[*params->i] == params->quote)
		(*params->i)++;
	return (res);
}

void	handle_quotes_in_word(t_word_params *params, int *local_quoted)
{
	char				*q_mark;
	char				*segment;
	t_extract_params	extract_params;

	q_mark = &params->line[*params->i];
	extract_params = (t_extract_params){params->line, params->i, params->env, 
		*q_mark, local_quoted};
	segment = extract_quoted_text(&extract_params);
	if (segment)
		*params->value = merge_strings(*params->value, segment, 1);
	if (params->was_quoted && *local_quoted)
		*params->was_quoted = 1;
}

static char	**create_first_arg(char *new_arg)
{
	char	**new_arr;

	new_arr = malloc(2 * sizeof(char *));
	if (!new_arr)
		return (NULL);
	new_arr[0] = ft_strdup(new_arg);
	new_arr[1] = NULL;
	return (new_arr);
}

char	**append_arg(char **args, char *new_arg)
{
	int		i;
	char	**new_arr;
	int		j;

	j = -1;
	if (!new_arg)
		return (args);
	if (!args)
		return (create_first_arg(new_arg));
	i = 0;
	while (args[i])
		i++;
	new_arr = malloc((i + 2) * sizeof(char *));
	if (!new_arr)
		return (NULL);
	while (++j < i)
		new_arr[j] = args[j];
	new_arr[i] = ft_strdup(new_arg);
	new_arr[i + 1] = NULL;
	free(args);
	return (new_arr);
}
