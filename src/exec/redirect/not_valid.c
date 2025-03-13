/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:34:14 by throbert          #+#    #+#             */
/*   Updated: 2025/03/12 02:08:04 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	not_valid_cmd2(t_shell *shell, char **cmd, char **cmd_files)
{
	if (is_only_quotes(cmd[0], 0) == 2)
		remove_quotes(cmd[0]);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_tab(cmd);
	free_all(shell, cmd_files);
	exit(127);
}

void	close_fd(t_shell *shell, int pipefd[2])
{
	if (shell->prev_fd != -1)
		close(shell->prev_fd);
	close(pipefd[1]);
	shell->prev_fd = pipefd[0];
	if (shell->error_flag)
		shell->error_flag = 0;
}
