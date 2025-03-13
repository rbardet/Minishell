/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambigous.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:51:51 by throbert          #+#    #+#             */
/*   Updated: 2025/02/28 01:07:37 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	process_redirect_token(char **token_cmd, int i)
{
	char	**expansion;
	int		file_count;

	if (token_cmd[i + 1])
	{
		if (contain_wildcard(token_cmd[i + 1]))
		{
			expansion = expand_token(token_cmd[i + 1]);
			file_count = ft_tablen(expansion);
			free_tab(expansion);
			if (file_count > 1)
				return (1);
		}
	}
	return (0);
}

static int	ambiguous_redirects_indexes(char **token_cmd, int *indexes)
{
	int	i;
	int	pipe_index;
	int	count;

	i = 0;
	pipe_index = 0;
	count = 0;
	while (token_cmd[i])
	{
		if (ft_strcmp(token_cmd[i], "|") == 0)
			pipe_index++;
		if (ft_strcmp(token_cmd[i], ">") == 0 || ft_strcmp(token_cmd[i],
				">>") == 0)
		{
			if (process_redirect_token(token_cmd, i))
				indexes[count++] = pipe_index;
		}
		i++;
	}
	return (count);
}

void	detect_ambiguous_redirects(char **token_cmd, t_shell *shell)
{
	int	indexes[1024];
	int	count;
	int	i;

	if (shell->indexes)
		free(shell->indexes);
	shell->indexes = NULL;
	count = ambiguous_redirects_indexes(token_cmd, indexes);
	if (count == 0)
		return ;
	shell->indexes = malloc(sizeof(int) * (count + 1));
	if (!shell->indexes)
		return ;
	i = 0;
	while (i < count)
	{
		shell->indexes[i] = indexes[i];
		i++;
	}
	shell->indexes[count] = -1;
}
