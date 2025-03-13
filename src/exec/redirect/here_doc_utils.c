/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 06:33:46 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 19:12:21 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_tmp_doc(int doc_count)
{
	char	*file;
	char	*tmp2;

	while (doc_count != 0)
	{
		tmp2 = ft_itoa(doc_count);
		file = ft_strjoin(".heredoc", tmp2);
		unlink(file);
		doc_count--;
		free(tmp2);
		free(file);
	}
}

int	do_here_doc(t_shell *shell, char **toks)
{
	int		i;
	char	**cmd;

	i = 0;
	cmd = split_for_doc(toks);
	while (cmd[i] != NULL)
	{
		if (!ft_strcmp(cmd[i], "<<"))
		{
			shell->doc_count++;
			if ((handle_doc(shell, i, cmd, toks)) == 130)
			{
				free_tab(cmd);
				free_tab(toks);
				remove_tmp_doc(shell->doc_count);
				shell->exit_code = 130;
				return (130);
			}
		}
		i++;
	}
	free_tab(cmd);
	return (0);
}
