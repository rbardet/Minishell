/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:34:46 by throbert          #+#    #+#             */
/*   Updated: 2025/03/09 04:15:00 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fork_and_exec(t_shell *shell, char **toks)
{
	pid_t	pid;
	int		status;

	(void)toks;
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork", 2);
		return (127);
	}
	if (pid == 0)
	{
		free_tab(toks);
		setup_signals(0);
		status = exec(shell->cmd, shell);
		if (status == 127)
		{
			free_tab(shell->env);
			free_tab(shell->env_for_sub);
			free_tab(shell->cmd);
			free(shell);
		}
		exit(status);
	}
	return (wait_ignore(pid));
}
