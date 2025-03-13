/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:19:36 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/28 01:09:46 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_suffix(char *dir_name, char *token)
{
	int	token_len;
	int	dir_len;

	token_len = ft_strlen(token);
	dir_len = ft_strlen(dir_name);
	if (dir_len > 1 && dir_name[dir_len - 1] == '/')
		dir_len--;
	if (dir_len < token_len)
		return (0);
	if (ft_strncmp(dir_name + (dir_len - token_len), token, token_len) != 0)
		return (0);
	return (1);
}

static int	is_prefix(char *flag)
{
	int	i;

	if (flag[0] != '*')
		i = 1;
	else
		i = 0;
	return (i);
}

static int	tokens_match_no_star(char **tokens, char *dir_name, int pos, int i)
{
	int	token_count;

	token_count = count_tokens_wild(tokens);
	if (token_count - i > 1)
	{
		if (!check_middle_tokens(dir_name, tokens + i, token_count - i - 1,
				&pos))
			return (0);
	}
	if (!check_suffix(dir_name, tokens[token_count - 1]))
		return (0);
	return (1);
}

static int	tokens_match(char **tokens, char *dir_name, char *flag)
{
	int	pos;
	int	i;
	int	token_count;

	token_count = count_tokens_wild(tokens);
	pos = 0;
	i = 0;
	if (token_count == 0)
		return (1);
	if (flag[0] != '*' && !check_prefix(dir_name, tokens[0], &pos))
		return (0);
	i = is_prefix(flag);
	if (flag[ft_strlen(flag) - 1] != '*')
		return (tokens_match_no_star(tokens, dir_name, pos, i));
	else
	{
		if (!check_middle_tokens(dir_name, tokens + i, token_count - i, &pos))
			return (0);
	}
	return (1);
}

int	match_pattern(char *dir_name, char *flag)
{
	char	**tokens;
	int		ret;
	int		len;

	len = ft_strlen(dir_name);
	if (len > 1 && dir_name[len - 1] == '/')
		dir_name[len - 1] = '\0';
	if (dir_name[0] == '.')
		return (0);
	if (!flag || ft_strcmp(flag, "*") == 0)
		return (1);
	tokens = ft_split(flag, '*');
	if (!tokens)
		return (0);
	ret = tokens_match(tokens, dir_name, flag);
	free_tab(tokens);
	return (ret);
}
