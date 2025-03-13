/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_par2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:22:21 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 20:37:20 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirections(char *tok, int *j)
{
	char	c;

	if (tok[*j] == '<' || tok[*j] == '>')
	{
		c = tok[*j];
		(*j)++;
		if (tok[*j] == c)
			(*j)++;
		while (tok[*j] == ' ')
			(*j)++;
		while (tok[*j] && tok[*j] != ' ' && tok[*j] != '(' && tok[*j] != ')')
			(*j)++;
		return (1);
	}
	return (0);
}

int	check_pipe(char *tok, int *j, int *last_type)
{
	if (tok[*j] == '|' && tok[*j + 1] != '|')
	{
		if (*last_type != 4 && *last_type != 2)
		{
			ft_putstr_fd("Minishell: syntax error near unexpected token `|'\n",
				2);
			return (2);
		}
		(*j)++;
		*last_type = 5;
		return (1);
	}
	return (0);
}

int	check_logical_ops(char *tok, int *j, int *last_type)
{
	if ((tok[*j] == '&' && tok[*j + 1] == '&')
		|| (tok[*j] == '|' && tok[*j + 1] == '|'))
	{
		if (*last_type != 4 && *last_type != 2)
		{
			ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
			write(2, &tok[*j], 2);
			ft_putstr_fd("'\n", 2);
			return (2);
		}
		(*j) += 2;
		*last_type = 3;
		return (1);
	}
	else if (tok[*j] == '&')
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `&'\n", 2);
		return (2);
	}
	return (0);
}

int	svp2(int i)
{
	if (i == 1)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `('\n", 2);
		return (2);
	}
	else
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `)'\n", 2);
		return (2);
	}
}

int	check_parentheses(char *tok, int *j, int *open_par, int *last_type)
{
	if (tok[*j] == '(')
	{
		if (*last_type == 2
			|| (*last_type == 0 && *j > 0 && tok[*j - 1] == ')'))
			return (svp2(1));
		(*open_par)++;
		*last_type = 1;
	}
	else if (tok[*j] == ')')
	{
		if (*open_par <= 0)
			return (svp2(2));
		(*open_par)--;
		*last_type = 2;
	}
	if (tok[*j])
		(*j)++;
	return (0);
}
