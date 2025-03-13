/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:25:44 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 20:30:48 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_cmd(char **cmd, char **env)
{
	char	**cmd_files;
	int		i;

	if (!cmd)
		return (1);
	cmd_files = split_path(cmd, env);
	if (!cmd_files)
		return (1);
	i = 0;
	while (cmd_files[i])
	{
		if (access(cmd_files[i], X_OK) == 0)
		{
			free_tab(cmd_files);
			return (0);
		}
		i++;
	}
	free_tab(cmd_files);
	return (1);
}

pid_t	process_cmd(t_shell *shell, int *wait_pid, char **toks)
{
	pid_t	pid;
	int		pipefd[2];

	if (!is_redirection(shell) && tab_size(shell->cmd) < 3)
		return (0);
	if (pipe(pipefd) == -1)
	{
		free_all(shell, NULL);
		ft_putstr_fd("pipe error\n", 2);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		free_all(shell, NULL);
		ft_putstr_fd("fork error\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		redirect_child(shell, pipefd, wait_pid, toks);
	close_fd(shell, pipefd);
	return (pid);
}

int	process_redirect(t_shell *shell, int *wait_pid, int j, char **toks)
{
	int	i;

	i = 0;
	if (is_ambiguous(shell, j) == 1)
		return (1);
	while (shell->cmd[i] != NULL && ft_strcmp(shell->cmd[i], "|"))
	{
		if (!ft_strcmp(shell->cmd[i], "<"))
		{
			shell->in_count++;
			if (redirect_input(shell, i) != 0)
				break ;
		}
		else if (!ft_strcmp(shell->cmd[i], ">") || (!ft_strcmp(shell->cmd[i],
					">>")))
		{
			shell->out_count++;
			if (redirect_output(shell, i) != 0)
				break ;
		}
		i++;
	}
	if ((shell->cmd[i] == NULL || !ft_strcmp(shell->cmd[i], "|")))
		return (process_cmd(shell, wait_pid, toks));
	return (1);
}

int	is_invalid_token(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i + 1])
	{
		if ((!ft_strcmp(cmd[i], "|") && !ft_strcmp(cmd[i + 1], "|"))
			|| ((!ft_strcmp(cmd[i], "<") || !ft_strcmp(cmd[i], ">")
					|| !ft_strcmp(cmd[i], "<<") || !ft_strcmp(cmd[i], ">>"))
				&& !ft_strcmp(cmd[i + 1], "|")))
		{
			write(2, "Minishell: syntax error near unexpected token '|'\n", 51);
			return (2);
		}
		if (((!ft_strcmp(cmd[i], "<") || !ft_strcmp(cmd[i], ">")
					|| !ft_strcmp(cmd[i], "<<") || !ft_strcmp(cmd[i], ">>"))
				&& (!ft_strcmp(cmd[i + 1], "<") || !ft_strcmp(cmd[i + 1], ">")
					|| !ft_strcmp(cmd[i + 1], "<<") || !ft_strcmp(cmd[i + 1],
						">>"))))
		{
			write(2, "Minishell: syntax error near unexpected token '<'\n", 51);
			return (2);
		}
		i++;
	}
	return (0);
}

int	redirect(t_shell *shell, char **toks)
{
	pid_t	pid;

	shell->pipe_count = count_pipe(shell->cmd);
	shell->size = tab_size(shell->cmd);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		redirect_loop(shell, toks);
	return (wait_ignore(pid));
}
