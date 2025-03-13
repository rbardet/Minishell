/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:48:09 by throbert          #+#    #+#             */
/*   Updated: 2025/03/11 23:54:08 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	contains_star(char *s, int start, int end)
{
	while (start < end)
	{
		if (s[start] == '*')
			return (1);
		start++;
	}
	return (0);
}

//  echo '$USER"$"\td""end'   in double quote to handle \ nested in ""
// in that cas we do not interpret the \t
//
// but if in single quote \t become litteral and in "" it becomes tab
void	handle_singlequote_content(char *in, int *i, char **w)
{
	int	in_double_quote;

	in_double_quote = 0;
	while (in[*i] && in[*i] != '\'')
	{
		if (in[*i] == '"')
			in_double_quote *= -1;
		if (in[*i] == '\\' && in_double_quote)
		{
			(*i)++;
			handle_single_escape(in[*i], w);
		}
		else
		{
			*w = append_char(*w, in[*i]);
			(*i)++;
		}
	}
}

// if $ skip it to handle $' case
// if * in the content copy all literally
// else copy wihtout single quote at begin and end
void	handle_singlequote(char *in, int *i, char **w)
{
	int	orig;
	int	end;

	if (in[*i] == '$')
		(*i)++;
	orig = *i;
	(*i)++;
	end = *i;
	while (in[end] && in[end] != '\'')
		end++;
	if (contains_star(in, orig, end + 1))
	{
		*i = orig;
		while (*i < end + 1)
			*w = append_char(*w, in[(*i)++]);
	}
	else
		handle_singlequote_content(in, i, w);
	if (in[*i] == '\'')
		(*i)++;
}

// go through each char and if special handle it else just append
static void	handle_special_chars(char *in, int *i, char **w, t_shell *shell)
{
	if (in[*i] == '(')
		capture_parentheses_content(in, i, w);
	else if (in[*i] == '\\' && !is_escaped(in, *i))
		handle_backslash(in, i, w);
	else if (in[*i] == '\'' && (*i == 0 || in[*i - 1] != '$'))
		handle_singlequote(in, i, w);
	else if (in[*i] == '"' && (*i == 0 || in[*i - 1] != '$'))
		handle_doublequote(in, i, w, shell);
	else if (in[*i] == '$')
	{
		if (in[*i + 1] == '\'')
			handle_ansi_c_quote(in, i, w);
		else if (in[*i + 1] == '"')
			handle_doublequote(in, i, w, shell);
		else
			handle_dollar(in, i, w, shell);
	}
	else if (in[*i] == '~' && ft_strlen(*w) == 0)
		*w = parse_tilde(in, i, *w, shell);
	else
	{
		*w = append_char(*w, in[*i]);
		(*i)++;
	}
}

char	*ft_parse_word(char *in, int *pos, t_shell *shell)
{
	char	*w;
	int		i;

	w = ft_strdup("");
	i = *pos;
	if (is_only_quotes(in, i))
	{
		while (in[i] && in[i] != '&' && in[i] != '|' && !ft_isspace(in[i]))
		{
			w = append_char(w, in[i]);
			i++;
		}
		*pos = i;
		return (w);
	}
	while (in[i] && !ft_isspace(in[i]))
		handle_special_chars(in, &i, &w, shell);
	*pos = i;
	return (w);
}
