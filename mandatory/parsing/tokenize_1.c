/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:00:21 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/01 17:46:15 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_token_type	get_char_type(char *line, int *i)
{
	int	pos;

	pos = *i;
	if (line[pos] == '>' && line[pos + 1] == '>')
		return (TOKEN_APPEND);
	if (line[pos] == '<' && line[pos + 1] == '<')
		return (TOKEN_HEREDOC);
	if (line[pos] == '|')
		return (TOKEN_PIPE);
	if (line[pos] == '>')
		return (TOKEN_REDIR_OUT);
	if (line[pos] == '<')
		return (TOKEN_REDIR_IN);
	return (TOKEN_WORD);
}

static void	copy_flags_and_add(int *flags, int *new_arr, int size, int new_flag)
{
	int	j;

	j = -1;
	while (++j < size)
		new_arr[j] = flags[j];
	new_arr[size] = new_flag;
	new_arr[size + 1] = -1;
}

int	*append_heredoc_flag(int *flags, int new_flag)
{
	int	i;
	int	*new_arr;

	if (!flags)
	{
		new_arr = malloc(2 * sizeof(int));
		if (!new_arr)
			return (NULL);
		new_arr[0] = new_flag;
		new_arr[1] = -1;
		return (new_arr);
	}
	i = 0;
	while (flags[i] && flags[i] != -1)
		i++;
	new_arr = malloc((i + 2) * sizeof(int));
	if (!new_arr)
		return (NULL);
	copy_flags_and_add(flags, new_arr, i, new_flag);
	free(flags);
	return (new_arr);
}

void	add_in_list(t_token **head, char *value, t_token_type type,
		int was_quoted)
{
	t_token	*new;
	t_token	*current;

	if (!head || !value)
		return ;
	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	new->type = type;
	new->was_quoted = was_quoted;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	read_env_name(char *line, int *i, t_env *env, char **res)
{
	char	*name;
	char	*value;
	int		start;
	char	*empty_str;

	start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	if (*i > start)
	{
		name = ft_substr(line, start, *i - start);
		if (name)
		{
			value = get_value(env, name);
			if (value)
				*res = merge_strings(*res, ft_strdup(value), 1);
			else
			{
				empty_str = ft_strdup("");
				*res = merge_strings(*res, empty_str, 1);
			}
			free(name);
		}
	}
}
