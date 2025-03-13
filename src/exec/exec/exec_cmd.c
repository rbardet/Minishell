/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:37:31 by throbert          #+#    #+#             */
/*   Updated: 2025/03/08 00:09:27 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

int	absolute_cmd(char **cmd, t_shell *shell)
{
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, shell->env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free_tab(shell->cmd);
	free_tab(shell->env);
	free_tab(shell->env_for_sub);
	free(shell);
	return (127);
}

int	exec_cmd2(char **cmd, char **paths_split, t_shell *shell, int j)
{
	char	*fp;

	fp = ft_strjoin(paths_split[j], "/");
	if (!fp)
		return (127);
	fp = ft_strjoin_free_both(fp, ft_strdup(cmd[0]));
	if (fp && access(fp, X_OK) == 0)
	{
		execve(fp, cmd, shell->env);
		free(fp);
		free_tab(paths_split);
		error_message(cmd);
		shell->exit_code = 127;
		free_tab(shell->cmd);
		free_tab(shell->env);
		free_tab(shell->env_for_sub);
		free(shell);
		exit(127);
	}
	free(fp);
	return (-1);
}

int	try_paths(char **paths_split, char **cmd, t_shell *shell)
{
	int	j;
	int	bool;

	j = 0;
	while (paths_split[j])
	{
		bool = exec_cmd2(cmd, paths_split, shell, j);
		if (bool != -1)
			return (bool);
		j++;
	}
	return (-1);
}

int	exec_cmd(char **cmd, t_shell *shell, char *pv)
{
	char	**paths_split;
	int		bool;

	paths_split = ft_split(pv, ':');
	free(pv);
	if (!paths_split)
	{
		error_message(cmd);
		shell->exit_code = 127;
		return (127);
	}
	bool = try_paths(paths_split, cmd, shell);
	free_tab(paths_split);
	if (bool != -1)
		return (bool);
	error_message(cmd);
	shell->exit_code = 127;
	return (127);
}
