/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_only_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 07:03:02 by throbert          #+#    #+#             */
/*   Updated: 2025/03/11 23:58:28 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_quotes_content(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			return (0);
		i++;
	}
	return (1);
}

static int	check_pairs(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (i + 1 >= len || str[i] != str[i + 1])
			return (2);
		i += 2;
	}
	return (1);
}

int	is_only_quotes(char *s, int i)
{
	int		start;
	int		end;
	char	*tmp;
	char	*trimmed;

	if ((s[i] == '&' && s[i + 1] == '&') || s[i] == '|')
		return (0);
	start = i;
	while (s[i] && s[i] != '|'
		&& !(s[i] == '&' && s[i + 1] == '&'))
		i++;
	end = i;
	tmp = ft_substr(s, start, end - start);
	trimmed = ft_strtrim(tmp, " \t");
	free(tmp);
	tmp = trimmed;
	if (!check_quotes_content(tmp))
	{
		free(tmp);
		return (0);
	}
	i = check_pairs(tmp);
	free(tmp);
	return (i);
}
