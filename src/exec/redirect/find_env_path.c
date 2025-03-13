/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 06:20:26 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/28 20:10:35 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// find the value of PATH in env
char	*find_env(char **env)
{
	int		i;
	int		j;
	char	*env_path;

	i = 0;
	j = 0;
	if (!env)
		return (NULL);
	while (env[i] != NULL)
	{
		j = ft_strncmp(env[i], "PATH=", 5);
		if (j == 0)
		{
			env_path = ft_strdup(env[i] + 5);
			return (env_path);
		}
		i++;
	}
	return (NULL);
}

char	**split_path(char **cmd, char **env)
{
	char	*path;
	char	**cmd_files;
	char	**files;
	char	*cmd_join;
	int		i;

	i = 0;
	path = find_env(env);
	if (!path)
		return (NULL);
	files = ft_split(path, ':');
	cmd_files = malloc(sizeof(char *) * (tab_size(files) + 1));
	if (!cmd_files)
		exit(EXIT_FAILURE);
	cmd_join = ft_strjoin("/", cmd[0]);
	while (files[i] != NULL)
	{
		cmd_files[i] = ft_strjoin(files[i], cmd_join);
		i++;
	}
	cmd_files[i] = NULL;
	free(path);
	free(cmd_join);
	free_tab(files);
	return (cmd_files);
}
