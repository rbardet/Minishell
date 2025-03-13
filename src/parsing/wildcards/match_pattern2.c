/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:41:14 by throbert          #+#    #+#             */
/*   Updated: 2025/02/28 01:08:53 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_tokens_wild(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

int	check_prefix(char *dir_name, char *token, int *pos)
{
	*pos = ft_strlen(token);
	if (ft_strncmp(dir_name, token, *pos) != 0)
		return (0);
	return (1);
}

int	check_middle_tokens(char *dir_name, char **subtokens, int cnt,
		int *pos)
{
	int		i;
	char	*found;

	i = 0;
	while (i < cnt)
	{
		found = ft_strnstr(dir_name + *pos, subtokens[i], ft_strlen(dir_name
					+ *pos));
		if (!found)
			return (0);
		*pos = (found - dir_name) + ft_strlen(subtokens[i]);
		i++;
	}
	return (1);
}
