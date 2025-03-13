/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:19:57 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 14:36:40 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*is_builtin(t_shell *s)
{
	if (!s || !s->cmd || !s->cmd[0])
		return (s);
	if (!ft_strcmp("cd", s->cmd[0]) || !ft_strcmp("pwd", s->cmd[0])
		|| !ft_strcmp("export", s->cmd[0]) || !ft_strcmp("unset", s->cmd[0])
		|| !ft_strcmp("env", s->cmd[0]) || !ft_strcmp("echo", s->cmd[0])
		|| !ft_strcmp("exit", s->cmd[0]))
		s->check = 0;
	else
		s->check = 1;
	return (s);
}

int	is_redirection(t_shell *s)
{
	int	i;

	i = 0;
	if (!s || !s->cmd || !s->cmd[0])
		return (1);
	if (tab_size(s->cmd) == 1)
		return (1);
	while (s->cmd[i])
	{
		if ((!ft_strcmp(s->cmd[i], "<")) || (!ft_strcmp(s->cmd[i], ">")
				|| (!ft_strcmp(s->cmd[i], "<<")) || (!ft_strcmp(s->cmd[i], "|"))
				|| (!ft_strcmp(s->cmd[i], ">>"))))
			return (0);
		i++;
	}
	return (1);
}

void	get_shlvl(t_shell *shell)
{
	int		shlvl;
	char	*shlvl_str;

	shlvl = ft_atoi(getenv("SHLVL")) + 1;
	shlvl_str = ft_itoa(shlvl);
	edit_env_value(shell, "SHLVL", shlvl_str);
	free(shlvl_str);
}

t_shell	*init_shell_env(t_shell *shell, char **env)
{
	int		env_count;
	int		i;

	env_count = tab_size(env);
	shell->env = malloc(sizeof(char *) * (env_count + 1));
	shell->env_for_sub = malloc(sizeof(char *) * (env_count + 1));
	i = -1;
	while (env[++i])
	{
		shell->env[i] = ft_strdup(env[i]);
		shell->env_for_sub[i] = ft_strdup(env[i]);
	}
	shell->env[i] = NULL;
	shell->env_for_sub[i] = NULL;
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	int		exit_code;

	(void)argv;
	if (argc != 1)
		return (1);
	setup_signals(1);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell = init_shell_env(shell, env);
	if (!shell->env)
		return (free(shell), 1);
	if (getenv("SHLVL"))
		get_shlvl(shell);
	shell->cmd = NULL;
	exit_code = shell_loop(shell);
	return (exit_code);
}
