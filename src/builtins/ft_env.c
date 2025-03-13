/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:30:15 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/04 03:59:49 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// edit the value that we want
// value is the value that want to change
// new_one is the value that will be the new one.
char	**edit_env_value(t_shell *shell, char *value, char *new_one)
{
	char	*tmp;
	char	*new_value;
	int		i;

	i = 0;
	if (!shell->env)
		return (NULL);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], value, ft_strlen(value)))
		{
			tmp = ft_strjoin(value, "=");
			new_value = ft_strjoin(tmp, new_one);
			free(shell->env[i]);
			shell->env[i] = new_value;
			free(tmp);
			break ;
		}
		i++;
	}
	return (shell->env);
}

// get the value that we want in the env of shell->env
char	*get_env(t_shell *shell, char *value)
{
	char	**tmp;
	char	*result;
	int		i;
	size_t	value_len;

	if (!shell || !shell->env || !value)
		return (NULL);
	result = NULL;
	tmp = NULL;
	value_len = ft_strlen(value);
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], value, value_len)
			&& shell->env[i][value_len] == '=')
		{
			tmp = ft_split(shell->env[i], '=');
			if (tmp && tmp[1])
				result = ft_strdup(tmp[1]);
			free_tab(tmp);
			return (result);
		}
		i++;
	}
	return (NULL);
}

// display the env in the terminal
int	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (tab_size(shell->cmd) > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(shell->cmd[1], 2);
		ft_putstr_fd("no such file or directory\n", 2);
		return (127);
	}
	if (!shell->env)
	{
		ft_putstr_fd("No env available.\n", 2);
		shell->exit_code = 1;
		return (shell->exit_code);
	}
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
		i++;
	}
	shell->exit_code = 0;
	return (shell->exit_code);
}
