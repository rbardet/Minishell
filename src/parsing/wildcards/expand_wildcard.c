/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:48:19 by throbert          #+#    #+#             */
/*   Updated: 2025/03/10 23:17:42 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**expand_token_quotes(char *token)
{
	char	**expansion;
	char	*tmp;

	expansion = malloc(sizeof(char *) * 2);
	if (!expansion)
		return (NULL);
	tmp = remove_quotes_wild(token);
	expansion[0] = ft_strdup(tmp);
	expansion[1] = NULL;
	free(tmp);
	return (expansion);
}

static int	count_matches(char *token)
{
	struct dirent	*entry;
	DIR				*curr_dir;
	int				count;

	count = 0;
	curr_dir = opendir(".");
	entry = readdir(curr_dir);
	while (entry)
	{
		if (match_pattern(entry->d_name, token))
			count++;
		entry = readdir(curr_dir);
	}
	closedir(curr_dir);
	return (count);
}

static char	**fill_expansion(char *token, int count)
{
	struct dirent	*entry;
	DIR				*curr_dir;
	int				j;
	char			**expansion;

	expansion = malloc(sizeof(char *) * (count + 1));
	j = 0;
	curr_dir = opendir(".");
	entry = readdir(curr_dir);
	while (entry)
	{
		if (match_pattern(entry->d_name, token))
		{
			expansion[j] = ft_strdup(entry->d_name);
			j++;
		}
		entry = readdir(curr_dir);
	}
	closedir(curr_dir);
	expansion[j] = NULL;
	return (expansion);
}

static char	**expand_token_wildcard(char *token)
{
	int		count;
	char	**expansion;

	count = count_matches(token);
	if (count == 0)
	{
		expansion = malloc(sizeof(char *) * 2);
		if (!expansion)
			return (NULL);
		expansion[0] = ft_strdup(token);
		expansion[1] = NULL;
		return (expansion);
	}
	return (fill_expansion(token, count));
}

char	**expand_token(char *token)
{
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		return (expand_token_quotes(token));
	return (expand_token_wildcard(token));
}
