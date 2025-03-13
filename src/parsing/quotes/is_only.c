/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_only.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:05:16 by throbert          #+#    #+#             */
/*   Updated: 2025/03/09 05:05:52 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// fc = first char
// will check if only backslashes
// or only `
// if \ and ` return error
// if other char return error
//
// if pair length return good
// non pair = error
int	is_only_backslashes_or_backtick(char *s)
{
	int		i;
	char	fc;

	if (!s || !*s)
		return (0);
	fc = s[0];
	if (fc != '\\' && fc != '`')
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] != fc)
			return (0);
		i++;
	}
	if (i % 2 == 0)
		return (0);
	return (1);
}
