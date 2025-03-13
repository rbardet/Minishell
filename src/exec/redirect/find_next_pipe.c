/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 02:51:28 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/23 00:35:14 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_pipe_index(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "|") != 0)
	{
		i++;
	}
	return (i);
}

char	**dup_after_pipe(char **cmd, int pipe_index)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = pipe_index + 1;
	new_cmd = malloc(sizeof(char *) * (tab_size(cmd) - i + 1));
	if (!new_cmd)
		return (NULL);
	j = 0;
	while (cmd[i])
	{
		new_cmd[j] = ft_strdup(cmd[i]);
		if (!new_cmd[j])
		{
			free_tab(new_cmd);
			return (NULL);
		}
		i++;
		j++;
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

char	**next_pipe(char **cmd)
{
	int		pipe_index;
	char	**new_cmd;

	pipe_index = find_pipe_index(cmd);
	if (!cmd[pipe_index])
	{
		free_tab(cmd);
		return (NULL);
	}
	new_cmd = dup_after_pipe(cmd, pipe_index);
	free_tab(cmd);
	return (new_cmd);
}
