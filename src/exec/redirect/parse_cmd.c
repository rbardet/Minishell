/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 06:31:28 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/09 04:17:26 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_res(char *res, char *line, int *r)
{
	int		i;
	int		dlen;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			quote(res, line, &i, r);
		else
		{
			dlen = is_delim(&line[i]);
			if (dlen)
			{
				append_delim(res, r, &line[i], dlen);
				i += dlen;
			}
			else
				res[(*r)++] = line[i++];
		}
	}
}

int	process_delimiter(char *line, int *j, char *current, int *count)
{
	int	dlen;

	dlen = is_delim(&line[*j]);
	if (dlen > 0)
	{
		if (*current == line[*j])
			*count += dlen;
		else
		{
			*current = line[*j];
			*count = dlen;
		}
		if ((*current != '|' && *current != '&') && *count > 2)
			return (1);
		*j += dlen;
		return (0);
	}
	*current = '\0';
	*count = 0;
	(*j)++;
	return (0);
}

int	update_count(char *line, int *j, int *count, char *current)
{
	char	quote;

	if (line[*j] == '\'' || line[*j] == '"')
	{
		quote = line[*j];
		(*j)++;
		while (line[*j] && line[*j] != quote)
			(*j)++;
		if (line[*j] == quote)
			(*j)++;
		*current = '\0';
		*count = 0;
		return (0);
	}
	return (process_delimiter(line, j, current, count));
}

int	check_line_delim_chain(char *line)
{
	int		j;
	int		count;
	char	current;

	j = 0;
	count = 0;
	current = '\0';
	while (line[j])
	{
		if (update_count(line, &j, &count, &current))
			return (1);
	}
	return (0);
}

char	*parse_cmd(char *line)
{
	int		r;
	char	*res;

	if (check_line_delim_chain(line))
		return (ft_strdup(""));
	res = ft_calloc(ft_strlen(line) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	r = 0;
	fill_res(res, line, &r);
	if (r > 0 && res[r - 1] == ' ')
		r--;
	res[r] = '\0';
	return (res);
}
