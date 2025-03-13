/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:33:01 by throbert          #+#    #+#             */
/*   Updated: 2025/03/07 19:28:46 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// escape
void	process_backslash(const char *s, char *clean, int *i, int *j)
{
	(*i)++;
	if (s[*i])
	{
		clean[(*j)++] = s[*i];
		(*i)++;
	}
}

// count backslash from last to first (all joined)
// if pair its escaped
int	is_escaped(char *s, int pos)
{
	int	count;

	count = 0;
	while (--pos >= 0 && s[pos] == '\\')
		count++;
	return (count % 2);
}

int	count_backslash(char *s, int pos)
{
	int	cnt;

	cnt = 0;
	pos--;
	while (pos >= 0 && s[pos] == '\\')
	{
		cnt++;
		pos--;
	}
	return (cnt);
}

void	handle_dollar_question(int *i, char **w, t_shell *shell)
{
	char	*tmp;

	tmp = ft_itoa(shell->exit_code);
	*w = append_str(*w, tmp);
	free(tmp);
	(*i) += 2;
}
