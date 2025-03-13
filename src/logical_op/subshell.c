/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/03/07 12:17:13 by throbert          #+#    #+#             */
/*   Updated: 2025/03/07 12:17:13 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// because we get (    )  subshell cmd in 1 char *
// we remove parenthese on 1 char *
// and realloc
char	*remove_parentheses(char *toks_i)
{
	int		len;
	char	*new_toks;

	if (!toks_i)
		return (NULL);
	len = ft_strlen(toks_i);
	if (len > 1 && toks_i[0] == '(' && toks_i[len - 1] == ')')
	{
		new_toks = ft_strndup(toks_i + 1, len - 2);
		return (new_toks);
	}
	return (toks_i);
}

// ft split like in process input line but goes through our parsing
// like a real prompt
// no need to go again through validate input because we already did it before
char	**parse_subshell(char *toks_i, t_shell *sub_shell)
{
	char	**subshell_toks;
	char	*parsed_trim;

	parsed_trim = remove_parentheses(toks_i);
	if (!parsed_trim)
		return (NULL);
	subshell_toks = ft_split_token(parsed_trim, sub_shell);
	free(parsed_trim);
	return (subshell_toks);
}

// init subshell same as shell
void	init_subshell(t_shell *sub_shell)
{
	sub_shell->cmd = NULL;
	sub_shell->env_for_sub = NULL;
	sub_shell->exit_code = 0;
	sub_shell->indexes = 0;
	sub_shell->in_single_quote = 0;
	sub_shell->in_double_quote = 0;
	sub_shell->pipe_count = 0;
	sub_shell->check = 0;
	sub_shell->save_in = 0;
	sub_shell->size = 0;
	sub_shell->j = 1;
	sub_shell->error_flag = 0;
	sub_shell->save_out = 0;
	sub_shell->in_count = 0;
	sub_shell->out_count = 0;
}

void	execute_child(t_shell *sub_shell, char **sub_commands, int status)
{
	init_subshell(sub_shell);
	execute_tokens(sub_shell, sub_commands);
	free_tab(sub_commands);
	free_tab(sub_shell->env);
	status = sub_shell->exit_code;
	free(sub_shell);
}

// we fork a children process that will init his shell
//
// execute token in his env
//
// the parent will wait for the children to finish
// and get the exit code
void	sub_fork(t_shell *sub_shell, char *toks_i, t_shell *shell,
		char **toks2)
{
	pid_t	pid;
	int		status;
	char	**sub_commands;

	status = 0;
	sub_commands = NULL;
	sub_commands = parse_subshell(toks_i, sub_shell);
	if (sub_commands == NULL)
		return ;
	pid = fork();
	if (pid == 0)
	{
		free_all(shell, toks2);
		execute_child(sub_shell, sub_commands, status);
		exit(status);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		shell->exit_code = WEXITSTATUS(status);
		free_tab(sub_commands);
	}
}

// (cat) ||  echo $?
// avec ctrl + z et ctrl + backslah print pas le bon

// ((ls) && echo)
