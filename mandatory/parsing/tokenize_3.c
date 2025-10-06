/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:10:23 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/03 18:31:29 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	handle_regular_word(t_regular_word_params *params)
{
	char			*value;
	int				quotes_flag;
	int				was_quoted;
	t_word_params	word_params;

	value = ft_strdup("");
	if (!value)
		return ;
	quotes_flag = 0;
	was_quoted = 0;
	word_params = (t_word_params){params->line, params->i, 
		params->env, &value, &was_quoted};
	while (params->line[*params->i] 
		&& !ft_chr(" \t><|", params->line[*params->i]))
	{
		if (params->line[*params->i] == '\'' || params->line[*params->i] == '"')
			quotes_flag = 1;
		check_word(&word_params);
	}
	if ((value && *value) || quotes_flag)
		add_in_list(params->tokens, value, TOKEN_WORD, was_quoted);
	free(value);
}

static void	handle_heredoc_delimiter(char *line, int *i,
		int *is_heredoc_delimiter, t_token **tokens)
{
	int		start;
	char	*value;

	start = *i;
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	start = *i;
	while (line[*i] && !ft_chr(" \t><|", line[*i]))
		(*i)++;
	if (*i > start)
	{
		value = ft_substr(line, start, *i - start);
		add_in_list(tokens, value, TOKEN_WORD, 0);
		free(value);
	}
	*is_heredoc_delimiter = 0;
}

static void	handle_non_word_token(t_token_type type, int *i,
		int *is_heredoc_delimiter, t_token **tokens)
{
	char	*empty_str;

	if (type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		(*i) += 2;
	else
		(*i) += 1;
	if (type == TOKEN_HEREDOC)
		*is_heredoc_delimiter = 1;
	else
		*is_heredoc_delimiter = 0;
	empty_str = ft_strdup("");
	add_in_list(tokens, empty_str, type, 0);
	free(empty_str);
}

void	add_token(char *line, int *i, t_env *env, t_token **tokens)
{
	t_token_type			type;
	static int				is_heredoc_delimiter = 0;
	t_regular_word_params	params;

	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	if (!line[*i])
		return ;
	type = get_char_type(line, i);
	if (type != TOKEN_WORD)
	{
		handle_non_word_token(type, i, &is_heredoc_delimiter, tokens);
		return ;
	}
	if (is_heredoc_delimiter)
	{
		handle_heredoc_delimiter(line, i, &is_heredoc_delimiter, tokens);
		return ;
	}
	params = (t_regular_word_params){line, i, env, tokens};
	handle_regular_word(&params);
	is_heredoc_delimiter = 0;
}
