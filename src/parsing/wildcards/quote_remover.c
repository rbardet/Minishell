/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:48:48 by throbert          #+#    #+#             */
/*   Updated: 2025/03/07 16:04:06 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ignore first ' et copy till next '
void	process_single_quote(const char *s, char *clean, int *i, int *j)
{
	(*i)++;
	while (s[*i] && s[*i] != '\'')
	{
		clean[(*j)++] = s[*i];
		(*i)++;
	}
	if (s[*i] == '\'')
		(*i)++;
}

// ignore first " et copy till next "
void	process_double_quote(const char *s, char *clean, int *i, int *j)
{
	(*i)++;
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '\\' && (s[*i + 1] == '\"' || s[*i + 1] == '\\' || s[*i
					+ 1] == '$'))
		{
			clean[(*j)++] = s[++(*i)];
			(*i)++;
		}
		else
		{
			clean[(*j)++] = s[(*i)++];
		}
	}
	if (s[*i] == '\"')
		(*i)++;
}

void	copy_without_quotes(char *s, char *clean)
{
	int	i;
	int	j;
	int	in_single_quote;

	i = 0;
	j = 0;
	in_single_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			in_single_quote = !in_single_quote;
			process_single_quote(s, clean, &i, &j);
		}
		else if (s[i] == '\"')
			process_double_quote(s, clean, &i, &j);
		else if (s[i] == '\\' && !is_escaped(s, i) && !in_single_quote)
			process_backslash(s, clean, &i, &j);
		else
			clean[j++] = s[i++];
	}
	clean[j] = '\0';
}

char	*remove_quotes_wild(char *s)
{
	char	*clean;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	clean = malloc(len + 1);
	if (!clean)
		return (NULL);
	copy_without_quotes(s, clean);
	return (clean);
}
