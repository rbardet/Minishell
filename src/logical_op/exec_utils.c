/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:35:09 by throbert          #+#    #+#             */
/*   Updated: 2025/03/13 16:34:59 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	preprocess_tokens(char **toks)
{
	int	i;

	i = 0;
	while (toks[i])
	{
		replace_double_operators(toks, &i);
		i++;
	}
}

int	check_tokens_start(t_shell *shell, char **toks)
{
	int	size;

	size = tab_size(toks);
	if (size == 0)
		return (0);
	if (!ft_strcmp(toks[0], "&&") || !ft_strcmp(toks[0], "||")
		|| !ft_strcmp(toks[0], "|") || !ft_strcmp(toks[size - 1], "&&")
		|| !ft_strcmp(toks[size - 1], "||")
		|| !ft_strcmp(toks[size - 1], "|"))
	{
		ft_putendl_fd("unclosed operator", 2);
		shell->exit_code = 2;
		return (2);
	}
	return (-1);
}

int	check_tokens_body(t_shell *shell, char **toks)
{
	int	i;
	int	size;

	size = tab_size(toks);
	i = 0;
	while (i < size)
	{
		if (!ft_strcmp(toks[i], "&&") || !ft_strcmp(toks[i], "||")
			|| !ft_strcmp(toks[i], "|"))
		{
			if (i + 1 < size && (!ft_strcmp(toks[i + 1], "&&")
					|| !ft_strcmp(toks[i + 1], "||")
					|| !ft_strcmp(toks[i + 1], "|")))
			{
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putstr_fd(toks[i + 1], 2);
				ft_putendl_fd("'", 2);
				shell->exit_code = 2;
				return (2);
			}
		}
		i++;
	}
	return (0);
}

int	check_tokens(t_shell *shell, char **toks)
{
	if (check_tokens_start(shell, toks) != -1)
		return (2);
	return (check_tokens_body(shell, toks));
}
