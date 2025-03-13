/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 01:54:43 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/09 04:24:21 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_pipe(char	**cmd)
{
	int	pipe_count;
	int	i;

	i = 0;
	pipe_count = 0;
	while (cmd[i] != NULL)
	{
		if (!ft_strcmp(cmd[i], "|"))
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

int	is_redirect(char *cmd)
{
	if (!ft_strcmp(cmd, "<") || !ft_strcmp(cmd, ">")
		|| !ft_strcmp(cmd, ">>") || !ft_strcmp(cmd, "<<"))
	{
		return (1);
	}
	return (0);
}

void	not_valid_cmd(t_shell *shell, char **cmd)
{
	if (cmd && cmd[0])
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	free_all(shell, cmd);
	exit(127);
}

void	check_next_pipe(t_shell *shell)
{
	char	**cmd;
	int		i;

	i = 0;
	if (!shell || !shell->cmd)
		return ;
	cmd = ft_calloc(tab_size(shell->cmd) + 1, sizeof(char *));
	while (shell->cmd && shell->cmd[i] && ft_strcmp(shell->cmd[i], "|"))
	{
		cmd[i] = ft_strdup(shell->cmd[i]);
		i++;
	}
	cmd[i] = NULL;
	if (cmd && cmd[0] && ((ft_tabtabchr(cmd, "<<") || ft_tabchr(cmd, '<'))))
		dup2(shell->save_in, STDIN_FILENO);
	dup2(shell->save_out, STDOUT_FILENO);
	free_tab(cmd);
}

int	is_ambiguous(t_shell *shell, int i)
{
	int	j;

	if (!shell->indexes)
		return (0);
	j = 0;
	while (shell->indexes[j] != -1)
	{
		if (shell->indexes[j] == i)
		{
			if (shell->prev_fd > 0)
				close(shell->prev_fd);
			ft_putstr_fd("Minishell: ambiguous redirect.\n", 2);
			return (1);
		}
		j++;
	}
	return (0);
}
