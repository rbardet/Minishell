/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:37:50 by throbert          #+#    #+#             */
/*   Updated: 2025/03/06 05:34:02 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_dollar_var_no_braces(char *in,
		int *i, char **w, t_shell *shell)
{
	int		start;
	int		j;
	char	*var_name;
	char	*var_value;

	start = (*i) + 1;
	j = start;
	if (!in[j] || (!ft_isalpha(in[j]) && in[j] != '_'))
	{
		*w = append_char(*w, '$');
		(*i)++;
		return ;
	}
	while (in[j] && (ft_isalnum(in[j]) || in[j] == '_'))
		j++;
	var_name = ft_substr(in, start, j - start);
	var_value = get_env_value(var_name, *shell);
	free(var_name);
	if (var_value)
	{
		*w = append_str(*w, var_value);
		free(var_value);
	}
	*i = j;
}

void	handle_dollar_var(char *in, int *i, char **w, t_shell *shell)
{
	if (in[*i + 1] == '{')
	{
		handle_dollar_braces(in, i, w, shell);
		return ;
	}
	handle_dollar_var_no_braces(in, i, w, shell);
}

int	handle_dollar_literal(char *in, int *i, char **w, t_shell *shell)
{
	char	next;

	next = in[*i + 1];
	if (!next || ft_isspace(next))
	{
		*w = append_char(*w, '$');
		(*i)++;
		return (1);
	}
	if ((count_backslash(in, *i) % 2) == 1)
	{
		*w = append_char(*w, '$');
		(*i)++;
		return (1);
	}
	if (!(ft_isalpha(next) || next == '_' || next == '?' || next == '{'))
	{
		*w = append_char(*w, '$');
		(*i)++;
		return (1);
	}
	(void)shell;
	return (0);
}

void	handle_dollar(char *in, int *i, char **w, t_shell *shell)
{
	char	next;

	next = in[*i + 1];
	if (!next || ft_isspace(next))
	{
		*w = append_char(*w, '$');
		(*i)++;
		return ;
	}
	if (!in[*i + 1] || ft_isspace(in[*i + 1])
		|| (!ft_isalpha(in[*i + 1]) && in[*i + 1] != '_'
			&& in[*i + 1] != '?' && in[*i + 1] != '{'))
	{
		*w = append_char(*w, '$');
		(*i)++;
		return ;
	}
	if (in[*i + 1] == '?')
		handle_dollar_question(i, w, shell);
	else if (in[*i + 1] == '{')
		handle_dollar_braces(in, i, w, shell);
	else
		handle_dollar_var(in, i, w, shell);
}
