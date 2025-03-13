/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:31:13 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 18:27:54 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*extract_heredoc_name(int *doc_count)
{
	char	*num_str;
	char	*heredoc_name;

	num_str = ft_itoa((*doc_count)++);
	heredoc_name = ft_strjoin(".heredoc", num_str);
	free(num_str);
	return (heredoc_name);
}

static char	*extract_heredoc_limit(char *after)
{
	int		limit_len;

	while (*after == ' ')
		after++;
	limit_len = 0;
	while (after[limit_len] && after[limit_len] != ' '
		&& after[limit_len] != ')' && after[limit_len] != '|')
		limit_len++;
	return (after + limit_len);
}

static char	*return_for_doc(char *new_str, char *before)
{
	if (new_str)
		free(new_str);
	if (before)
		free(before);
	return (NULL);
}

static char	*get_heredoc_name_and_replacement(char *before,
	int *doc_count, char *after)
{
	char	*heredoc_name;
	char	*temp;
	char	*new_str;

	heredoc_name = extract_heredoc_name(doc_count);
	if (!heredoc_name)
	{
		free(before);
		return (NULL);
	}
	temp = ft_strjoin(before, "< ");
	free(before);
	if (!temp)
		return (return_for_doc(heredoc_name, NULL));
	before = temp;
	temp = ft_strjoin(before, heredoc_name);
	free(before);
	free(heredoc_name);
	if (!temp)
		return (NULL);
	before = temp;
	new_str = ft_strjoin(before, after);
	free(before);
	return (new_str);
}

char	*replace_heredoc_in_str(char *str, int *doc_count)
{
	char	*new_str;
	char	*pos;
	char	*before;
	char	*after;
	char	*temp_new_str;

	new_str = ft_strdup(str);
	if (!new_str)
		return (NULL);
	pos = ft_strstr(new_str, "<<");
	while (pos)
	{
		before = ft_strndup(new_str, pos - new_str);
		after = extract_heredoc_limit(pos + 2);
		if (!before || !after)
			return (return_for_doc(new_str, before));
		temp_new_str = get_heredoc_name_and_replacement(before,
				doc_count, after);
		if (!temp_new_str)
			return (return_for_doc(new_str, before));
		free(new_str);
		new_str = temp_new_str;
		pos = ft_strstr(new_str, "<<");
	}
	return (new_str);
}
