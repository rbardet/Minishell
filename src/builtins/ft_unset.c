/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:08:10 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/28 02:27:18 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Get all the args after unset, they are the values to be deleted
// from the env.
char	**get_unset_value(t_shell *shell)
{
	char	**get_args;
	char	*tmp;
	int		i;
	int		j;

	i = 1;
	j = 0;
	get_args = ft_calloc(tab_size(shell->cmd), sizeof(char *));
	while (shell->cmd[i])
	{
		tmp = get_env(shell, shell->cmd[i]);
		if (tmp)
		{
			get_args[j] = ft_strdup(shell->cmd[i]);
			free(tmp);
			j++;
		}
		i++;
	}
	get_args[j] = NULL;
	return (get_args);
}

static char	**update_env(t_shell *shell, int pos)
{
	int	size;

	size = tab_size(shell->env);
	free(shell->env[pos]);
	while (pos < size - 1)
	{
		shell->env[pos] = shell->env[pos + 1];
		pos++;
	}
	shell->env[size - 1] = NULL;
	return (shell->env);
}

t_shell	*unset_loop(t_shell *shell, char **get_args, int i, int j)
{
	while (get_args[i])
	{
		j = 0;
		while (shell->env[j])
		{
			if (!ft_strncmp(get_args[i], shell->env[j], ft_strlen(get_args[i]))
				&& (shell->env[j][ft_strlen(get_args[i])] == '='
				|| shell->env[j][ft_strlen(get_args[i])] == '\0'))
			{
				shell->env = update_env(shell, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (shell);
}

// Unset all the values after "unset" if they exist
t_shell	*ft_unset(t_shell *shell)
{
	char	**get_args;
	int		i;
	int		j;

	if (!shell || !shell->cmd || !shell->env)
		return (shell);
	shell->exit_code = 0;
	if (!shell->cmd[1])
		return (shell);
	get_args = shell->cmd + 1;
	if (!get_args)
		return (shell);
	i = 0;
	j = 0;
	shell = unset_loop(shell, get_args, i, j);
	return (shell);
}
