/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 04:57:45 by throbert          #+#    #+#             */
/*   Updated: 2025/03/13 15:16:36 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_subshell(char *toks_i, t_shell *shell, char **toks2)
{
	t_shell	*sub_shell;

	sub_shell = malloc(sizeof(t_shell));
	if (!sub_shell)
		return ;
	sub_shell->env = ft_tabdup(shell->env_for_sub);
	sub_fork(sub_shell, toks_i, shell, toks2);
	if (sub_shell->env)
		free_tab(sub_shell->env);
	free(sub_shell);
}
