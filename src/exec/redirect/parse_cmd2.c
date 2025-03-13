/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:19:28 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 01:04:45 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_delim(char *s)
{
	if (s[0] == '<' && s[1] == '<')
		return (2);
	if (s[0] == '>' && s[1] == '>')
		return (2);
	if (s[0] == '&' && s[1] == '&')
		return (2);
	if (s[0] == '|' && s[1] == '|')
		return (2);
	if (s[0] == '(' || s[0] == ')')
		return (1);
	if (s[0] == '<' || s[0] == '>' || s[0] == '|' || s[0] == '&')
		return (1);
	return (0);
}

void	process_delim(char *line, int *i, int *len, char *prev)
{
	int		dlen;
	char	c;

	dlen = is_delim(&line[*i]);
	c = line[*i];
	if (dlen == 1 && (c == '(' || c == ')'))
	{
		if (*prev != ' ' && *prev != '(' && *prev != ')')
			(*len)++;
		(*len) += 1;
		*prev = c;
		(*i)++;
		if (line[*i] && line[*i] != ' ' && !is_delim(&line[*i]))
			(*len)++;
	}
	else
	{
		if (*prev != ' ')
			(*len)++;
		*len += dlen;
		if (line[*i + dlen] && line[*i + dlen] != ' ')
			(*len)++;
		*i += dlen;
		*prev = ' ';
	}
}

void	handle_quotes(char *line, int *i, int *len, char *prev)
{
	char	quote;

	quote = line[*i];
	(*len)++;
	*prev = line[(*i)++];
	while (line[*i] && line[*i] != quote)
	{
		(*len)++;
		*prev = line[*i];
		(*i)++;
	}
	if (line[*i] == quote)
	{
		(*len)++;
		*prev = line[*i];
		(*i)++;
	}
}

int	calc_len_line(char *line)
{
	int		i;
	int		len;
	char	prev;

	i = 0;
	len = 0;
	prev = ' ';
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			handle_quotes(line, &i, &len, &prev);
		else if (is_delim(&line[i]))
			process_delim(line, &i, &len, &prev);
		else
		{
			len++;
			prev = line[i];
			i++;
		}
	}
	return (len);
}
