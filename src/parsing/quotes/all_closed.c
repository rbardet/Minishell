/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:16:40 by throbert          #+#    #+#             */
/*   Updated: 2025/03/06 11:34:08 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_single(char *s, int i, int state[4])
{
	if (s[i] == '\'')
		state[0] = 0;
	return (i);
}

// in double quote either check if on backslash + if an escapble is present and
// put in ESCAPE (3) if it is
// or close if on "
static int	handle_double(char *s, int i, int state[4])
{
	if (s[i] == '\\' && (s[i + 1] == '$' || s[i + 1] == '"'
			|| s[i + 1] == '`' || s[i + 1] == '\\'))
		state[3] = 1;
	else if (s[i] == '"')
		state[1] = 0;
	return (i);
}

// echo 'It\'s a test' = unclosed bc \ do not escpae the '
// so 3  single quote '  are left
int	handle_backslash3(char *s, int i, int state[4])
{
	while (s[i])
	{
		if (s[i] == '\'')
		{
			state[2] = 0;
			return (i);
		}
		i++;
	}
	return (i);
}

// will go through the string and check one by one the quote state
// state is maj here and in all closed simultaneously
static int	process_quotes(char *s, int state[4])
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (state[3])
			state[3] = 0;
		else if (state[0])
			i = handle_single(s, i, state);
		else if (state[1])
			i = handle_double(s, i, state);
		else if (state[2])
			i = handle_backslash3(s, i, state);
		else
			i = handle_normal(s, i, state);
		if (s[i])
			i++;
	}
	return (i);
}

// escape (3) only in normal and double.
// if 1 state is one = unclosed quote
int	all_quotes_closed(char *s)
{
	int	state[4];

	state[0] = 0;
	state[1] = 0;
	state[2] = 0;
	state[3] = 0;
	process_quotes(s, state);
	return (!state[0] && !state[1] && !state[2]);
}

//  && !state[3]
