/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_backslash_backtick.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 05:00:56 by throbert          #+#    #+#             */
/*   Updated: 2025/03/06 05:00:56 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// go through the string and count the number of backslashes
// if the number is odd, there is an unclosed backslash
//
// Backslash can be be unclosd JUST if last char of str.
// that why if found other than backshlash, reset the count
static int	check_unclosed_backslash(char *str)
{
	int	i;
	int	backslash_count;

	i = 0;
	backslash_count = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			backslash_count++;
		else
			backslash_count = 0;
		i++;
	}
	if (backslash_count % 2 == 1)
	{
		ft_putstr_fd("Unclosed backslash\n", 2);
		return (1);
	}
	return (0);
}

// count number  backslash bef  backtick (go back to check)
// if  number is not pair the backtick is escaped
static int	skip_escaped_backticks(char *str, int i)
{
	int	backslash_count;

	backslash_count = 0;
	while (i > 0 && str[i - 1] == '\\')
	{
		backslash_count++;
		i--;
	}
	if (backslash_count % 2 == 1)
		return (1);
	return (0);
}

static int	check_unclosed_backtick(char *str)
{
	int	tick_count;
	int	i;
	int	in_single_quote;

	tick_count = 0;
	i = 0;
	in_single_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_single_quote = !in_single_quote;
		if (str[i] == '`' && !in_single_quote)
		{
			if (!skip_escaped_backticks(str, i))
				tick_count++;
		}
		i++;
	}
	if (tick_count % 2 == 1)
	{
		ft_putstr_fd("Unclosed backtick\n", 2);
		return (1);
	}
	return (0);
}

int	validate_only_backslash_tick(t_shell *shell, char *str)
{
	if (check_unclosed_backslash(str))
	{
		shell->exit_code = 2;
		return (1);
	}
	if (check_unclosed_backtick(str))
	{
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}
