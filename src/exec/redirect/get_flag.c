/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:30:19 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/28 19:56:02 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_command_index(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "<") || !ft_strcmp(cmd[i], ">")
			|| !ft_strcmp(cmd[i], ">>") || !ft_strcmp(cmd[i], "<<"))
		{
			i += 2;
		}
		else
		{
			break ;
		}
	}
	return (i);
}

int	is_delim_token(char *token)
{
	int		j;
	char	*base;

	j = 0;
	base = "<>|";
	while (base[j])
	{
		if (token[0] == base[j])
			return (1);
		j++;
	}
	return (0);
}

static char	**ft_malloc(t_shell *shell)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * (tab_size(shell->cmd) + 1));
	if (!cmd)
		return (NULL);
	return (cmd);
}

static int	copy_arg(char **args, char **cmd, int *i, int *j)
{
	if (is_redirect(cmd[*i]))
		*i += 2;
	else
	{
		args[*j] = ft_strdup(cmd[*i]);
		if (!args[*j])
		{
			return (1);
		}
		(*j)++;
		(*i)++;
	}
	return (0);
}

char	**get_flag(t_shell *shell)
{
	char	**args;
	int		i;
	int		j;

	if (!shell || !shell->cmd || !shell->cmd[0])
		return (NULL);
	args = ft_malloc(shell);
	i = 0;
	j = 0;
	while (shell->cmd[i] && ft_strcmp(shell->cmd[i], "|") != 0)
	{
		if (copy_arg(args, shell->cmd, &i, &j))
		{
			free_tab(args);
			return (NULL);
		}
	}
	args[j] = NULL;
	if (j == 0)
	{
		free(args);
		return (NULL);
	}
	return (args);
}
