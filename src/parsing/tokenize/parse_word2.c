/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:26:12 by throbert          #+#    #+#             */
/*   Updated: 2025/03/07 12:26:12 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// prend le homme de l env
// l append
char	*parse_tilde(char *in, int *i, char *w, t_shell *shell)
{
	char	*home;

	if (!in[*i + 1] || in[*i + 1] == '/' || ft_isspace(in[*i + 1]))
	{
		home = get_env_value("HOME", *shell);
		if (!home)
		{
			home = getenv("HOME");
			if (home)
				w = append_str(w, home);
			else
				w = append_char(w, '~');
		}
		else
		{
			w = append_str(w, home);
			free(home);
		}
	}
	else
		w = append_char(w, '~');
	(*i)++;
	return (w);
}

// if find another (  increase level
// if find ) decrease level
// if level == 0 break because its the last )
// else append all char in btw
static void	process_parentheses(char *in, int *i, char **w, int *paren_level)
{
	while (in[*i])
	{
		if (in[*i] == '(')
			(*paren_level)++;
		else if (in[*i] == ')')
		{
			(*paren_level)--;
			if (*paren_level == 0)
			{
				*w = append_char(*w, in[*i]);
				(*i)++;
				break ;
			}
		}
		*w = append_char(*w, in[*i]);
		(*i)++;
	}
}

// paren level in cas parentehse in parentehse to know where is real end
// apprend the first '('  and start loop
void	capture_parentheses_content(char *in, int *i, char **w)
{
	int	paren_level;

	paren_level = 1;
	*w = append_char(*w, in[*i]);
	(*i)++;
	process_parentheses(in, i, w, &paren_level);
}

void	process_doublequote_content(char *in,
			int *i, char **w, t_shell *shell)
{
	while (in[*i] && in[*i] != '"')
	{
		if (in[*i] == '\\')
			handle_backslash_sequence_in_doublequote(in, i, w, shell);
		else if (in[*i] == '$')
			handle_dollar(in, i, w, shell);
		else
			*w = append_char(*w, in[(*i)++]);
	}
	if (in[*i] == '"')
		(*i)++;
}

// if * same as in single quote2
// else process double
// handle the $' case
void	handle_doublequote(char *in, int *i, char **w, t_shell *shell)
{
	int	orig;
	int	end;

	if (in[*i] == '$')
		(*i)++;
	orig = *i;
	(*i)++;
	end = *i;
	while (in[end] && in[end] != '"')
		end++;
	if (contains_star(in, orig, end + 1))
	{
		*i = orig;
		while (*i < end + 1)
			*w = append_char(*w, in[(*i)++]);
	}
	else
		process_doublequote_content(in, i, w, shell);
}
