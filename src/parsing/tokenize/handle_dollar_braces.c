/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_braces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 05:33:58 by throbert          #+#    #+#             */
/*   Updated: 2025/03/06 05:33:58 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*extract_var_name(char *in, int *i, int start)
{
	char	*var_name;
	int		j;

	j = *i;
	var_name = ft_substr(in, start, j - start);
	(*i)++;
	return (var_name);
}

void	handle_dollar_braces(char *in, int *i, char **w, t_shell *shell)
{
	int		start;
	char	*var_name;
	char	*var_value;

	*i += 2;
	start = *i;
	while (in[*i] && in[*i] != '}')
	{
		if (in[*i] == '\\' && !is_escaped(in, *i))
			(*i)++;
		(*i)++;
	}
	if (!in[*i])
	{
		*w = append_str(*w, "${");
		return ;
	}
	var_name = extract_var_name(in, i, start);
	var_value = get_env_value(var_name, *shell);
	free(var_name);
	if (var_value)
	{
		*w = append_str(*w, var_value);
		free(var_value);
	}
}
