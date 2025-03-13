/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:36:29 by throbert          #+#    #+#             */
/*   Updated: 2025/03/04 08:11:01 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// check first cmd is in path
// check first cmd is in path
int	check_first(char *argv, char **env)
{
	char	**cmd;
	char	**files;
	int		i;

	cmd = ft_split(argv, ' ');
	if (!cmd[0])
		return (free(cmd), 1);
	files = split_env_path(cmd, env);
	i = 0;
	if (files)
	{
		while (files[i])
		{
			if (access(files[i], X_OK) == 0)
			{
				free_tab(cmd);
				free_tab(files);
				return (0);
			}
			i++;
		}
	}
	free_tab(cmd);
	free_tab(files);
	return (1);
}

// if / in cmd  = abolute path
// if do not exist error
// else  exec_cmd try every path
int	exec(char **cmd, t_shell *shell)
{
	char	*path;

	if (!cmd || !cmd[0])
		return (127);
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, shell->env);
	if (check_first(cmd[0], shell->env) != 0)
	{
		error_message(cmd);
		shell->exit_code = 127;
		return (127);
	}
	path = get_env_value("PATH", *shell);
	if (!path || !path[0])
	{
		error_message(cmd);
		shell->exit_code = 127;
		if (path)
			free(path);
		return (127);
	}
	return (exec_cmd(cmd, shell, path));
}

int	check_single_cmd(t_shell *shell, char **cmd)
{
	if (cmd && cmd[0])
	{
		if (access(cmd[0], X_OK) == 0)
			return (0);
		if (check_first(cmd[0], shell->env))
		{
			shell->exit_code = 127;
			return (1);
		}
	}
	return (0);
}
