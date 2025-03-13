/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 08:42:10 by throbert          #+#    #+#             */
/*   Updated: 2025/03/06 08:42:10 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// substr extre the in btw content of backtick
// trim it
// check if empty
static int	is_empty_backtick(char *s, int start, int end)
{
	char	*content;
	char	*trimmed;
	int		is_empty;

	content = ft_substr(s, start + 1, end - start - 1);
	if (!content)
		return (0);
	trimmed = ft_strtrim(content, " \t\n");
	is_empty = (trimmed && ft_strlen(trimmed) == 0);
	free(content);
	free(trimmed);
	return (is_empty);
}

// if last is back tick + not escaped by pair nb of baclsahes
static int	process_backtick_content(char *s, int start, int end)
{
	if (s[end] == '`' && !is_escaped(s, start))
	{
		if (is_empty_backtick(s, start, end))
			return (1);
	}
	return (0);
}

// k = just after backtick
// till before end (last `)
// copy everytihng in btw
//
// if just empty backtick we return 
int	handle_closed_backtick(char *s, int *i, char *res, int *j)
{
	int	start;
	int	end;
	int	k;

	start = *i;
	end = start + 1;
	while (s[end] && s[end] != '`')
		end++;
	if (s[end] == '`')
	{
		if (process_backtick_content(s, start, end))
		{
			*i = end + 1;
			return (0);
		}
		k = start + 1;
		while (k < end)
			res[(*j)++] = s[k++];
		*i = end + 1;
	}
	return (1);
}
