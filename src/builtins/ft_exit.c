/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 22:55:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 20:00:09 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit error message in case the exit code contain a non numeric
// argument.
static void	exit_error_message(t_shell *shell, char **toks)
{
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(shell->cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_exit(shell, toks);
	exit(2);
}

void	free_exit(t_shell *shell, char **toks)
{
	if (toks)
		free_tab(toks);
	if (shell->cmd)
		free_tab(shell->cmd);
	if (shell->env)
		free_tab(shell->env);
	if (shell->env_for_sub)
		free_tab(shell->env_for_sub);
	free(shell);
}

// process the verification if the exit value is valid or no

long long	exit_limits(t_shell *shell, int i, long long status, char **toks)
{
	if (shell->cmd[1][0] == '-' || shell->cmd[1][0] == '+')
		i = 1;
	if ((shell->cmd[1][0] == '-' || shell->cmd[1][0] == '+')
		&& shell->cmd[1][1] == '\0')
		exit_error_message(shell, toks);
	while (shell->cmd[1][i])
	{
		if (!ft_isdigit(shell->cmd[1][i]))
			exit_error_message(shell, toks);
		i++;
	}
	return (status);
}

void	exit_message(t_shell *shell)
{
	if (shell->j == 0)
		ft_putstr_fd("exit\n", 2);
}

long long	ft_exit(t_shell *shell, char **toks)
{
	long long	status;
	int			error;
	int			i;

	i = 0;
	exit_message(shell);
	if (!shell->cmd[1])
	{
		status = shell->exit_code;
		(free_exit(shell, toks), exit(status));
	}
	status = ft_atol_safe(shell->cmd[1], &error);
	if (ft(shell->cmd[1]) == 1)
	{
		if (tab_size(shell->cmd) > 2)
		{
			ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
			return (1);
		}
	}
	if (error)
		exit_error_message(shell, toks);
	status = exit_limits(shell, i, status, toks);
	free_exit(shell, toks);
	exit(status);
}
