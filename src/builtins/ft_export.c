/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:25:48 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/08 02:46:46 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// check is the value to be added is valid
static int	is_valid_identifier(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	no_arg_export(t_shell *shell)
{
	int		i;
	char	**split;
	char	**sorted_env;
	char	*tmp;

	sorted_env = sort_str_tab(shell->env);
	i = 0;
	while (sorted_env[i] != NULL)
	{
		split = ft_split(sorted_env[i], '=');
		if (split[1])
			tmp = ft_strjoin("declare -x ", sorted_env[i]);
		else
			tmp = ft_strjoin("declare -x ", split[0]);
		ft_printf("%s\n", tmp);
		free(tmp);
		free_tab(split);
		i++;
	}
	free_tab(sorted_env);
}

// add a value to the env
static char	**add_value(t_shell *shell, char *arg)
{
	char	**new_env;
	int		j;

	new_env = ft_calloc(tab_size(shell->env) + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	j = 0;
	while (shell->env[j])
	{
		new_env[j] = shell->env[j];
		j++;
	}
	new_env[j] = ft_strdup(arg);
	new_env[j + 1] = NULL;
	free(shell->env);
	return (new_env);
}

// add a value if it exist or remove it
static void	update_or_add(t_shell *shell, char *arg)
{
	char	**split;
	int		j;

	split = ft_split(arg, '=');
	if (!split)
		return ;
	j = 0;
	while (shell->env[j])
	{
		if (!ft_strncmp(split[0], shell->env[j], ft_strlen(split[0]))
			&& (shell->env[j][ft_strlen(split[0])] == '='
			|| shell->env[j][ft_strlen(split[0])] == '\0'))
		{
			free(shell->env[j]);
			shell->env[j] = ft_strdup(arg);
			free_tab(split);
			return ;
		}
		j++;
	}
	shell->env = add_value(shell, arg);
	free_tab(split);
}

// reproduce export function wich change or add a value to the env
t_shell	*ft_export(t_shell *shell)
{
	int	i;

	shell->exit_code = 0;
	if (!shell->cmd[1])
	{
		no_arg_export(shell);
		return (shell);
	}
	i = 1;
	while (shell->cmd[i])
	{
		if (!is_valid_identifier(shell->cmd[i]))
		{
			ft_printf("minishell: export: %s: not a valid identifier\n",
				shell->cmd[i]);
			shell->exit_code = 1;
		}
		else
			update_or_add(shell, shell->cmd[i]);
		i++;
	}
	return (shell);
}
