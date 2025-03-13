/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xD.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:44:15 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 17:20:14 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_words(char *str)
{
	char	*dup;
	char	*token;
	int		count;

	count = 0;
	dup = ft_strdup(str);
	if (!dup)
		return (0);
	token = ft_strtok(dup, " ");
	while (token)
	{
		count++;
		token = ft_strtok(NULL, " ");
	}
	free(dup);
	return (count);
}

char	**split_spaces(char *str)
{
	char	**result;
	char	*dup;
	char	*token;
	int		i;

	dup = ft_strdup(str);
	if (!dup)
		return (NULL);
	result = malloc((count_words(str) + 1) * sizeof(char *));
	if (!result)
	{
		free(dup);
		return (NULL);
	}
	i = 0;
	token = ft_strtok(dup, " ");
	while (token)
	{
		result[i++] = ft_strdup(token);
		token = ft_strtok(NULL, " ");
	}
	result[i] = NULL;
	free(dup);
	return (result);
}
