/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:39:36 by hhammiou          #+#    #+#             */
/*   Updated: 2025/10/03 18:45:55 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	skip_dollar_before_quote(t_word_params *params)
{
	if (params->line[*params->i] == '$' && (params->line[*params->i + 1] == '"' 
			|| params->line[*params->i + 1] == '\''))
		(*params->i)++;
}

static int	is_expandable_variable(t_word_params *params)
{
	char	next_char;

	next_char = params->line[*params->i + 1];
	return (params->line[*params->i] == '$' 
		&& (ft_isalnum(next_char) || next_char == '_' || next_char == '?'));
}

static int	is_tilde_expansion(t_word_params *params)
{
	char	next_char;
	int		prev_char_valid;

	next_char = params->line[*params->i + 1];
	prev_char_valid = (*params->i == 0 || params->line[*params->i - 1] == ' ');
	return (params->line[*params->i] == '~' 
		&& (next_char == '/' || !next_char || next_char == ' ') 
		&& prev_char_valid);
}

static void	handle_tilde_expansion_in_word(t_word_params *params)
{
	char	*home_path;

	(*params->i)++;
	home_path = get_value(params->env, "HOME");
	if (home_path)
		*params->value = merge_strings(*params->value,
				ft_strdup(home_path), 1);
}

void	check_word(t_word_params *params)
{
	int	local_quoted;

	local_quoted = 0;
	skip_dollar_before_quote(params);
	if (params->line[*params->i] == '"' || params->line[*params->i] == '\'')
		handle_quotes_in_word(params, &local_quoted);
	else if (is_expandable_variable(params))
		expand_var(params->line, params->i, params->env, params->value);
	else if (is_tilde_expansion(params))
		handle_tilde_expansion_in_word(params);
	else
		append_char_to_str(params->line[(*params->i)++], params->value);
}
