/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:50:53 by throbert          #+#    #+#             */
/*   Updated: 2025/03/13 20:29:28 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// count because it will evovle btw each malloc
void	build_cmd(t_shell *shell, char **toks, int count)
{
	int	i;

	i = 0;
	shell->cmd = malloc(sizeof(char *) * (count + 1));
	if (!shell->cmd)
		return ;
	while (i < count)
	{
		shell->cmd[i] = ft_strdup(toks[i]);
		i++;
	}
	shell->cmd[i] = NULL;
}

void	execute_single_command(t_shell *shell, char **toks)
{
	int	i;

	i = 0;
	while (shell->cmd[i])
	{
		if (is_only_quotes(shell->cmd[i], 0))
			remove_quotes(shell->cmd[i]);
		i++;
	}
	if (shell->cmd && shell->cmd[0])
	{
		if (is_redirection(shell) == 0)
			shell->exit_code = redirect(shell, toks);
		else if (is_builtin(shell)->check == 0)
			shell->exit_code = exec_builtin(shell->cmd, shell, toks);
		else if (check_single_cmd(shell, shell->cmd)
			&& !ft_tabchr(shell->cmd, '*'))
		{
			error_message(shell->cmd);
			shell->exit_code = 127;
		}
		else
			shell->exit_code = fork_and_exec(shell, toks);
	}
}

// end take i to always know where the last command was
// and search the end of the current command (till next control operator)
//
// end will copie every thing from i to end in shell->cmd to skip the cmd
//  alreayd done
// get wildcard if any
//
//  *i = end - 1;  in case we have echo sdad asd ads asd. to not stay on echo.
// allow to stay on last word before the operator
//
// because before build cmd echo asad ads asd  is on 1 line
// after it will be one word in each case
// of the tab
// [0] echo asad ads asd
//
// becomes
// [0] : echo
// [1] : asad
// [2] : ads
// [3] : asd
void	execute_command(t_shell *shell, char **toks, int *i, int *exec_next)
{
	int	end;

	if (*exec_next)
	{
		end = *i;
		while (toks[end] && !(ft_strcmp(toks[end], "&&") == 0
				|| ft_strcmp(toks[end], "||") == 0))
			end++;
		build_cmd(shell, &toks[*i], end - *i);
		shell->cmd = expand_wildcard(shell->cmd, shell);
		execute_single_command(shell, toks);
		free_tab(shell->cmd);
		shell->cmd = NULL;
		*exec_next = (shell->exit_code == 0);
		*i = end - 1;
	}
}

int	handle_cycle(t_shell *shell)
{
	char	**toks;

	shell->save_out = 0;
	shell->error_flag = 0;
	shell->in_single_quote = 0;
	shell->in_double_quote = 0;
	shell->pipe_count = 0;
	toks = process_input_line(shell);
	if (!toks)
		return (-1);
	if (invalid_par(toks) == 2)
	{
		free_tab(toks);
		shell->exit_code = 2;
		return (2);
	}
	if (do_here_doc(shell, toks) == 130)
		return (shell->exit_code);
	toks = replace_doc(toks);
	execute_tokens(shell, toks);
	if (toks)
		free_tab(toks);
	return (0);
}

int	shell_loop(t_shell *shell)
{
	int	cycle_status;

	shell->exit_code = 0;
	shell->indexes = 0;
	while (1)
	{
		shell->in_count = 0;
		shell->out_count = 0;
		shell->doc_count = 0;
		shell->check = 0;
		shell->save_in = 0;
		shell->size = 0;
		shell->j = 0;
		cycle_status = handle_cycle(shell);
		remove_tmp_doc(shell->doc_count);
		if (cycle_status == -1)
			break ;
	}
	clear_history();
	free(shell->indexes);
	free_tab(shell->env);
	free_tab(shell->env_for_sub);
	cycle_status = shell->exit_code;
	free(shell);
	return (cycle_status);
}
