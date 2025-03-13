/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:43:41 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 15:24:51 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_exec_loop(t_shell *shell, int *wait_pid, char **toks, int j)
{
	int	exit_code;
	int	i;

	i = 0;
	exit_code = 0;
	while (shell->pipe_count != -1)
	{
		shell->j = 1;
		shell->in_count = 0;
		shell->out_count = 0;
		shell->save_out = dup(STDOUT_FILENO);
		wait_pid[i] = process_redirect(shell, wait_pid, i, toks);
		shell->cmd = next_pipe(shell->cmd);
		check_next_pipe(shell);
		shell->pipe_count--;
		i++;
		close(shell->save_out);
		close(shell->save_in);
	}
	while (j < i)
	{
		exit_code = wait_ignore(wait_pid[j]);
		j++;
	}
	return (exit_code);
}

void	redirect_loop(t_shell *shell, char **toks)
{
	pid_t	*wait_pid;
	int		exit_code;
	int		i;
	int		j;

	i = 0;
	j = 0;
	exit_code = 0;
	shell->prev_fd = -1;
	wait_pid = malloc(sizeof(pid_t) * (shell->pipe_count + 1));
	shell->save_in = dup(STDIN_FILENO);
	exit_code = redirect_exec_loop(shell, wait_pid, toks, j);
	if (shell->prev_fd > 0)
		close(shell->prev_fd);
	free(shell->indexes);
	free_all(shell, toks);
	free(wait_pid);
	exit(exit_code);
}

void	do_redirect(t_shell *shell, int pipefd[2])
{
	int	null_fd;

	if (shell->error_flag)
	{
		null_fd = open("/dev/null", O_RDONLY);
		if (null_fd >= 0)
		{
			dup2(null_fd, STDIN_FILENO);
			close(null_fd);
		}
	}
	else if (shell->prev_fd > 0 && shell->in_count == 0)
		dup2(shell->prev_fd, STDIN_FILENO);
	if (shell->prev_fd > 0)
		close(shell->prev_fd);
	if (shell->pipe_count != 0 && shell->out_count == 0)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	close(shell->save_in);
	close(shell->save_out);
}

static void	exit_builtin(t_shell *shell, char **toks, char **cmd)
{
	free_tab(shell->cmd);
	shell->cmd = cmd;
	exec_builtin(shell->cmd, shell, toks);
	free_all(shell, toks);
	exit(0);
}

void	redirect_child(t_shell *shell, int pipefd[2], int *wait_ignore,
		char **toks)
{
	char	**cmd;
	int		status;

	free(wait_ignore);
	do_redirect(shell, pipefd);
	cmd = get_flag(shell);
	if (!cmd)
	{
		free_all(shell, toks);
		exit(0);
	}
	if (cmd[0][0] == '(' && cmd[0][ft_strlen(cmd[0]) - 1] == ')')
	{
		free_tab(toks);
		shell->j = 1;
		execute_subshell(cmd[0], shell, cmd);
		status = shell->exit_code;
		free_all(shell, cmd);
		exit (status);
	}
	if (is_builtin(shell)->check == 0)
		exit_builtin(shell, toks, cmd);
	free_tab(toks);
	binary_path(cmd, shell);
	exec_path(cmd, shell);
}
