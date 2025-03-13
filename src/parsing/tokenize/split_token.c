/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:48:23 by throbert          #+#    #+#             */
/*   Updated: 2025/03/07 20:24:06 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// like count word count every token sep by space
int	count_tokens(char *in)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (in[i])
	{
		while (in[i] && ft_isspace(in[i]))
			i++;
		if (!in[i])
			break ;
		while (in[i] && !ft_isspace(in[i]))
			i++;
		cnt++;
	}
	return (cnt);
}

// like split but parse word will parse $ quote etc
static void	fill_tokens(char *in, t_shell *shell, char **tokens)
{
	int		i;
	int		n;
	char	*word;

	i = 0;
	n = 0;
	while (in[i])
	{
		while (in[i] && ft_isspace(in[i]))
			i++;
		if (!in[i])
			break ;
		word = ft_parse_word(in, &i, shell);
		tokens[n++] = ft_strdup(word);
		free(word);
	}
	tokens[n] = NULL;
}

char	**ft_split_token(char *in, t_shell *shell)
{
	char	**tokens;
	int		cnt;

	in = parse_cmd(in);
	cnt = count_tokens(in);
	tokens = malloc(sizeof(char *) * (cnt + 1));
	if (!tokens)
		return (NULL);
	fill_tokens(in, shell, tokens);
	free(in);
	return (tokens);
}
