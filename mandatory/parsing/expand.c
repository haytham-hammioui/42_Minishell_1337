/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:01:38 by hhammiou          #+#    #+#             */
/*   Updated: 2025/10/01 10:28:41 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static char	*expand_variable(char *value, int *i, t_env *env)
{
	int		start;
	char	*var;
	char	*val;
	char	*result;

	start = ++(*i);
	while (ft_isalnum(value[*i]) || value[*i] == '_')
		(*i)++;
	var = ft_substr(value, start, *i - start);
	if (!var)
		return (NULL);
	val = get_env_val(var, env);
	free(var);
	if (val)
		result = ft_strdup(val);
	else
		result = ft_strdup("");
	return (result);
}

char	*expand_word(char *value, t_env *env)
{
	int		i;
	char	*result;
	char	*temp;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] && (ft_isalpha(value[i + 1])
				|| value[i + 1] == '_'))
		{
			temp = expand_variable(value, &i, env);
			if (!temp)
				return (free(result), NULL);
			result = strjoin_free(result, temp);
		}
		else
			result = strjoin_free_c(result, value[i++]);
		if (!result)
			return (NULL);
	}
	return (result);
}

void	ft_expand(t_token *tokens, t_env *env)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if ((tmp->type == TOKEN_WORD || tmp->type == TOKEN_DOUBLE_QUOTED)
			&& tmp->type != TOKEN_SINGLE_QUOTED && tmp->value
			&& ft_strchr2(tmp->value, '$'))
			tmp->value = expand_word(tmp->value, env);
		tmp = tmp->next;
	}
}
