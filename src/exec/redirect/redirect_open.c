/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:47:55 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/12 02:08:55 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_file_2(t_shell *shell, int i, int check)
{
	int	fd;

	fd = 0;
	if (check == 2)
	{
		fd = open(shell->cmd[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
		dup2(fd, STDOUT_FILENO);
	}
	if (check == 3)
	{
		fd = open(shell->cmd[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0777);
		dup2(fd, STDOUT_FILENO);
	}
	if (fd < 0 && access(shell->cmd[i + 1], F_OK) == -1)
	{
		error_open(shell, i, 1, 2);
		return (1);
	}
	if (access(shell->cmd[i + 1], W_OK) == -1)
	{
		error_open(shell, i, 2, 2);
		return (1);
	}
	close(fd);
	return (0);
}

int	open_file(t_shell *shell, int i, int check)
{
	int	fd;

	fd = 0;
	if (check == 1)
	{
		fd = open(shell->cmd[i + 1], O_RDONLY);
		if (is_last_input(shell, i) == 0)
			dup2(fd, STDIN_FILENO);
		if (fd < 0 && access(shell->cmd[i + 1], F_OK) == -1)
		{
			error_open(shell, i, 1, 1);
			return (1);
		}
		if (access(shell->cmd[i + 1], R_OK) == -1)
		{
			error_open(shell, i, 2, 1);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	redirect_output(t_shell *shell, int i)
{
	if (!ft_strcmp(">", shell->cmd[i]))
		return (open_file_2(shell, i, 2));
	else
		return (open_file_2(shell, i, 3));
}

int	is_last_input(t_shell *shell, int i)
{
	int	j;

	j = i + 1;
	while (shell->cmd[j] && ft_strcmp(shell->cmd[j], "|"))
	{
		if (!ft_strcmp(shell->cmd[j], "<") || !ft_strcmp(shell->cmd[j], "<<"))
			return (1);
		j++;
	}
	return (0);
}

int	redirect_input(t_shell *shell, int i)
{
	if (!ft_strcmp("<", shell->cmd[i]))
		return (open_file(shell, i, 1));
	else
		return (1);
}
