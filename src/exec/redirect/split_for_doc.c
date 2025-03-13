/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:43:33 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 17:30:46 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	process_normal_token(char **new, char **split, int *j, int *k)
{
	char	*temp;

	temp = ft_strdup(split[*k]);
	if (!temp)
		return (0);
	new[*j] = temp;
	(*j)++;
	*k = *k + 1;
	return (1);
}

static int	process_token_split(char **new, char **split, int *j)
{
	int		k;
	int		result;

	k = 0;
	while (split[k])
	{
		result = handle_heredoc_token(new, split, j, &k);
		if (result == 1)
			continue ;
		result = process_normal_token(new, split, j, &k);
		if (result == 0)
			return (0);
	}
	return (1);
}

static char	**process_single_token(char *token, char **new, int *j)
{
	char	*tmp;
	char	**split;

	tmp = ft_strtrim(token, "()");
	if (!tmp)
		return (NULL);
	split = split_spaces(tmp);
	free(tmp);
	if (!split)
		return (NULL);
	if (process_token_split(new, split, j) == 0)
	{
		free_tab(split);
		return (NULL);
	}
	free_tab(split);
	return (new);
}

static char	**fill_split_tokens(char **toks, char **new)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (toks[i])
	{
		if (process_single_token(toks[i], new, &j) == NULL)
			return (NULL);
		i++;
	}
	new[j] = NULL;
	return (new);
}

char	**split_for_doc(char **toks)
{
	char	**new;
	int		total_count;

	total_count = count_split_tokens(toks);
	if (total_count < 0)
		return (NULL);
	new = malloc((total_count + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	return (fill_split_tokens(toks, new));
}
