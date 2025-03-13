/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:59:44 by throbert          #+#    #+#             */
/*   Updated: 2025/03/11 23:59:44 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quotes(char *s)
{
	int		i;
	int		j;
	char	quote;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				s[j++] = s[i++];
			if (s[i] == quote)
				i++;
		}
		else
			s[j++] = s[i++];
	}
	s[j] = '\0';
}

void	process_token(t_shell *shell, char **toks, int *i, int *exec_next)
{
	int	is_subshell;
	int	prev_is_op;
	int	next_is_op;
	int	nothing_after;

	is_subshell = (toks[*i][0] == '('
			&& toks[*i][ft_strlen(toks[*i]) - 1] == ')');
	prev_is_op = (*i > 0) && (!ft_strcmp(toks[*i - 1], "&&")
			|| !ft_strcmp(toks[*i - 1], "||"));
	next_is_op = toks[*i + 1] && (!ft_strcmp(toks[*i + 1], "&&")
			|| !ft_strcmp(toks[*i + 1], "||"));
	nothing_after = (toks[*i + 1] == NULL);
	if (*exec_next && is_subshell
		&& (prev_is_op || next_is_op || nothing_after))
		execute_subshell(toks[*i], shell, toks);
	else if (!ft_strcmp(toks[*i], "&&") || !ft_strcmp(toks[*i], "||"))
		*exec_next = handle_logical_operators(toks, *i, shell);
	else if (*exec_next)
		execute_command(shell, toks, i, exec_next);
}

int	skip_pipe_or_empty_cmd(t_shell *shell, char **toks, int *i)
{
	if (toks[*i][0] == '|' && toks[*i][1] == '\0' && toks[*i + 1]
		&& is_only_quotes(toks[*i + 1], 0) != 0)
	{
		(*i)++;
		return (1);
	}
	if (is_only_quotes(toks[*i], 0) == 1)
	{
		ft_putstr_fd("Command '' not found\n", 2);
		shell->exit_code = 127;
		(*i)++;
		return (1);
	}
	if (is_only_quotes(toks[*i], 0) == 2)
	{
		remove_quotes(toks[*i]);
		ft_putstr_fd(toks[*i], 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_code = 127;
		(*i)++;
		return (1);
	}
	return (0);
}

void	execute_tokens_loop(t_shell *shell, char **toks)
{
	int	i;
	int	exec_next;

	i = 0;
	exec_next = 1;
	while (toks[i])
	{
		if (skip_pipe_or_empty_cmd(shell, toks, &i))
			continue ;
		process_token(shell, toks, &i, &exec_next);
		i++;
	}
}

void	execute_tokens(t_shell *shell, char **toks)
{
	preprocess_tokens(toks);
	if (check_tokens(shell, toks))
		return ;
	execute_tokens_loop(shell, toks);
}
