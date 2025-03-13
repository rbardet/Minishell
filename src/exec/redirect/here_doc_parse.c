/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:54:11 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 18:22:08 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	process_simple_heredoc(char **cmd, int i, int *doc_count)
{
	char	*num_str;
	char	*new_token;

	free(cmd[i]);
	cmd[i] = ft_strdup("<");
	num_str = ft_itoa((*doc_count)++);
	new_token = ft_strjoin(".heredoc", num_str);
	free(num_str);
	free(cmd[i + 1]);
	cmd[i + 1] = new_token;
}

static int	process_heredoc_cmd(char **cmd, int *i, int *doc_count)
{
	char	*new_cmd;

	new_cmd = replace_heredoc_in_str(cmd[*i], doc_count);
	if (!new_cmd)
	{
		free(cmd[*i]);
		cmd[*i] = NULL;
		return (0);
	}
	free(cmd[*i]);
	cmd[*i] = new_cmd;
	return (1);
}

char	**replace_doc(char **cmd)
{
	int	i;
	int	doc_count;

	i = 0;
	doc_count = 1;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<<") == 0)
		{
			process_simple_heredoc(cmd, i, &doc_count);
			i += 2;
		}
		else if (ft_strstr(cmd[i], "<<"))
		{
			if (!process_heredoc_cmd(cmd, &i, &doc_count))
				return (NULL);
			i++;
		}
		else
			i++;
	}
	return (cmd);
}
