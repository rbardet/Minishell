/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/03/04 17:01:15 by throbert          #+#    #+#             */
/*   Updated: 2025/03/04 17:01:15 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// if last append backslash
// if $ \\ or " skip the \ and append the next char the char in question
void	handle_backslash_sequence_in_doublequote(char *in, int *i, char **w,
		t_shell *shell)
{
	(void)shell;
	if (in[*i + 1] == '\\' || in[*i + 1] == '$' || in[*i + 1] == '"')
	{
		*w = append_char(*w, in[*i + 1]);
		*i += 2;
	}
	else
	{
		*w = append_char(*w, '\\');
		(*i)++;
	}
}

// If unpair number of backslash
// backslashe escapes itself if he4s not the last char
void	handle_backslash(char *in, int *i, char **w)
{
	if (in[*i + 1])
	{
		(*i)++;
		*w = append_char(*w, in[*i]);
		(*i)++;
	}
	else
	{
		*w = append_char(*w, '\\');
		(*i)++;
	}
}

// for case of single quote in double quote with \t or other
// wile treat litteraly the char BUT bc in double will inteprete it
void	handle_single_escape(char c, char **w)
{
	if (c == 'n')
		*w = append_char(*w, '\n');
	else if (c == 't')
		*w = append_char(*w, '\t');
	else if (c == 'r')
		*w = append_char(*w, '\r');
	else if (c == 'b')
		*w = append_char(*w, '\b');
	else if (c == 'a')
		*w = append_char(*w, '\a');
	else if (c == 'v')
		*w = append_char(*w, '\v');
	else if (c == 'f')
		*w = append_char(*w, '\f');
	else if (c == '\\')
		*w = append_char(*w, '\\');
	else if (c == '\'')
		*w = append_char(*w, '\'');
	else
	{
		*w = append_char(*w, '\\');
		*w = append_char(*w, c);
	}
}

void	process_escape_sequence(char *in, int *i, char **w)
{
	(*i)++;
	if (in[*i] == 'n')
		*w = append_char(*w, '\n');
	else if (in[*i] == 't')
		*w = append_char(*w, '\t');
	else if (in[*i] == 'r')
		*w = append_char(*w, '\r');
	else if (in[*i] == '\\')
		*w = append_char(*w, '\\');
	else if (in[*i] == '"')
		*w = append_char(*w, '"');
	else if (in[*i] == '\'')
		*w = append_char(*w, '\'');
	else if (in[*i] == '$')
	{
		*w = append_char(*w, '\\');
		*w = append_char(*w, '$');
	}
	else
		*w = append_char(*w, in[*i]);
	(*i)++;
}

void	handle_ansi_c_quote(char *in, int *i, char **w)
{
	*i += 2;
	while (in[*i] && in[*i] != '\'')
	{
		if (in[*i] == '\\')
			process_escape_sequence(in, i, w);
		else
		{
			*w = append_char(*w, in[*i]);
			(*i)++;
		}
	}
	if (in[*i] == '\'')
		(*i)++;
}
