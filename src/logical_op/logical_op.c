/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 04:10:45 by throbert          #+#    #+#             */
/*   Updated: 2025/03/09 04:53:42 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Si && suit &&  alors ner unextpect &&  . si && et rien apres = unclosed &&
//
//
static void	replace_double_operators2(char **toks, int *i)
{
	int	j;

	free(toks[*i]);
	free(toks[*i + 1]);
	toks[*i] = ft_strdup("&&");
	j = *i + 1;
	while (toks[j])
	{
		toks[j] = toks[j + 1];
		j++;
	}
	(*i)--;
}

// go throguh the toks array
// if find | and | in i+1 then replace | with || and free the case in i+1
// same with &&
// it allow to avec || et && tout coller with the command like true&&echo d
// because parse cmd has split it all
void	replace_double_operators(char **toks, int *i)
{
	int	j;

	if (toks[*i] && toks[*i + 1] && ft_strcmp(toks[*i], "|") == 0
		&& ft_strcmp(toks[*i + 1], "|") == 0)
	{
		free(toks[*i]);
		free(toks[*i + 1]);
		toks[*i] = ft_strdup("||");
		j = *i + 1;
		while (toks[j])
		{
			toks[j] = toks[j + 1];
			j++;
		}
		(*i)--;
	}
	else if (toks[*i] && toks[*i + 1] && ft_strcmp(toks[*i], "&") == 0
		&& ft_strcmp(toks[*i + 1], "&") == 0)
		replace_double_operators2(toks, i);
}

// If precedent is not 0 and its && then return 0 which will skip the current
// command
// opposit for ||
// juste skip bc if then antother operator is valid it will still work even
// if the 7
// precendent are skipped
// ls asdasd && ls && ls || ls  the || will work with the first ls  even
//it ther others
// were skipped
int	handle_logical_operators(char **toks, int i, t_shell *shell)
{
	if (ft_strcmp(toks[i], "&&") == 0)
	{
		if (shell->exit_code != 0)
			return (0);
	}
	else if (ft_strcmp(toks[i], "||") == 0)
	{
		if (shell->exit_code == 0)
			return (0);
		return (1);
	}
	return (1);
}
