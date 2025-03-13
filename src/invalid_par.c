/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_par.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:28:39 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 20:36:50 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	svp(void)
{
	ft_putstr_fd("Minishell: unclosed parenthesis\n", 2);
	return (2);
}

static int	process_command(char *token, int *j, int *last_type)
{
	while (token[*j] == ' ')
		(*j)++;
	if (token[*j] && token[*j] != '(' && token[*j] != ')')
	{
		*last_type = 4;
		while (token[*j] && token[*j] != ' '
			&& token[*j] != '(' && token[*j] != ')')
			(*j)++;
	}
	return (0);
}

static int	handle_parenthesis_case(char *t, int *j, int *o_par, int *l_type)
{
	int	status;

	if (t[*j] == '(' || t[*j] == ')')
	{
		status = check_parentheses(t, j, o_par, l_type);
		if (status)
			return (status);
	}
	return (0);
}

static int	process_single_token(char *token, int *open_par, int *last_type)
{
	int	j;
	int	status;

	j = 0;
	while (token[j])
	{
		if (check_redirections(token, &j))
			continue ;
		status = check_logical_ops(token, &j, last_type);
		if (status != 0)
			return (status);
		status = handle_parenthesis_case(token, &j, open_par, last_type);
		if (status != 0)
			return (status);
		status = process_command(token, &j, last_type);
		if (status != 0)
			return (status);
	}
	return (0);
}

int	invalid_par(char **toks)
{
	int	i;
	int	status;
	int	open_par;
	int	last_type;

	i = 0;
	open_par = 0;
	last_type = 0;
	while (toks[i])
	{
		status = process_single_token(toks[i], &open_par, &last_type);
		if (status)
			return (status);
		i++;
	}
	if (open_par != 0)
		return (svp());
	return (0);
}
