/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:37:16 by throbert          #+#    #+#             */
/*   Updated: 2025/02/27 19:43:55 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_dirs(char **env)
{
	char	*pathvar;
	char	**dirs;
	int		i;

	pathvar = 0;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			pathvar = env[i] + 5;
			break ;
		}
		i++;
	}
	if (!pathvar)
		return (NULL);
	dirs = ft_split(pathvar, ':');
	return (dirs);
}

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

char	*build_single_path(char *dir, char *cmd0)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin_free_both(tmp, ft_strdup(cmd0));
	return (res);
}

char	**build_cmd_paths(char **dirs, char *cmd0)
{
	char	**res;
	int		i;
	int		count;

	count = tab_size(dirs);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
	{
		free_tab(dirs);
		return (NULL);
	}
	i = 0;
	while (dirs[i])
	{
		res[i] = build_single_path(dirs[i], cmd0);
		if (!res[i])
		{
			free_tab(dirs);
			free_tab(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

// split PATH in miultiple /bin/  + appen name of cmd
char	**split_env_path(char **cmd, char **env)
{
	char	**dirs;
	char	**res;

	if (!cmd[0])
		return (NULL);
	dirs = get_dirs(env);
	if (!dirs)
		return (NULL);
	res = build_cmd_paths(dirs, cmd[0]);
	free_tab(dirs);
	return (res);
}
