/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_backticks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 06:56:40 by throbert          #+#    #+#             */
/*   Updated: 2025/03/06 08:45:00 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// go from current i to end end check if backtick
// (should becasue checked before)
static int	handle_backtick(char *s, int *i, char *res, int *j)
{
	int	start;
	int	end;

	start = *i;
	end = start + 1;
	while (s[end] && s[end] != '`')
		end++;
	if (s[end] == '`')
		return (handle_closed_backtick(s, i, res, j));
	while (s[*i])
		res[(*j)++] = s[(*i)++];
	return (1);
}

// treat only ` or \ + ` just after
// else just copy the char
static void	process_fill(char *s, char *res, int *i, int *j)
{
	if (s[*i] == '\\' && s[*i + 1] && s[*i + 1] == '`')
	{
		(*i)++;
		handle_backtick(s, i, res, j);
	}
	else if (s[*i] == '`')
		handle_backtick(s, i, res, j);
	else
		res[(*j)++] = s[(*i)++];
}

// s = single
// d = double
// if is quote fill actualize s or d
// 
// if not fill result will call process fill
int	skip_quotes(char c, int *s, int *d)
{
	if (c == '\'' && !(*d))
	{
		*s = !(*s);
		return (1);
	}
	if (c == '"' && !(*s))
	{
		*d = !(*d);
		return (1);
	}
	return (0);
}

// actualize quote if its quote
// if not quote procces fill
//
// j is for the result
// i is for the input
char	*fill_result(char *s, int *in_single, int *in_double)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	*in_single = 0;
	*in_double = 0;
	while (s[i])
	{
		if (skip_quotes(s[i], in_single, in_double) || *in_single)
			res[j++] = s[i++];
		else
			process_fill(s, res, &i, &j);
	}
	res[j] = '\0';
	return (res);
}

char	*remove_empty_backticks(char *s)
{
	int		in_single;
	int		in_double;
	char	*res;

	if (!s)
		return (NULL);
	res = fill_result(s, &in_single, &in_double);
	return (res);
}
