/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_doc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:12:58 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 17:20:09 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_tokens_in_split(char **split)
{
	int		count;
	int		k;

	count = 0;
	k = 0;
	while (split[k])
	{
		if (ft_strcmp(split[k], "<<") == 0 && split[k + 1])
		{
			count = count + 2;
			k = k + 2;
		}
		else
		{
			count = count + 1;
			k = k + 1;
		}
	}
	return (count);
}

int	count_tokens_in_str(char *str)
{
	int		count;
	char	**split;
	char	*tmp;

	tmp = ft_strtrim(str, "()");
	if (tmp == NULL)
		return (-1);
	split = split_spaces(tmp);
	free(tmp);
	if (split == NULL)
		return (-1);
	count = count_tokens_in_split(split);
	free_tab(split);
	return (count);
}

int	count_split_tokens(char **toks)
{
	int	total;
	int	i;
	int	count;

	total = 0;
	i = 0;
	while (toks[i])
	{
		count = count_tokens_in_str(toks[i]);
		if (count < 0)
			return (-1);
		total = total + count;
		i = i + 1;
	}
	return (total);
}

int	handle_heredoc_token(char **new, char **split, int *j, int *k)
{
	char	*temp;

	if (ft_strcmp(split[*k], "<<") == 0 && split[*k + 1])
	{
		temp = ft_strdup("<<");
		if (!temp)
			return (0);
		new[*j] = temp;
		(*j)++;
		temp = ft_strdup(split[*k + 1]);
		if (!temp)
			return (0);
		new[*j] = temp;
		(*j)++;
		*k = *k + 2;
		return (1);
	}
	return (0);
}
