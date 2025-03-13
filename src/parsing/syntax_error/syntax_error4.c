/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:25:31 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 20:30:21 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_par(char *s)
{
	int	i;
	int	newline;

	i = 0;
	newline = 0;
	i++;
	while (s[i])
	{
		if (s[i] == ')')
			return (0);
		if (s[i] == '(')
			newline = 1;
		i++;
	}
	if (newline == 1)
		return (2);
	else
		return (1);
}

int	err_par(char sym)
{
	if (sym == '(')
		ft_putstr_fd("Unclosed parenthesis\n", 2);
	else if (sym == ')')
		ft_putstr_fd("minishell: syntax error near unexpected token `)'\n",
			2);
	return (2);
}

int	new_line_err(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
		2);
	return (1);
}

int	err_curly2(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `}'\n",
		2);
	return (1);
}
