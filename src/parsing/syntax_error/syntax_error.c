/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:52:34 by throbert          #+#    #+#             */
/*   Updated: 2025/03/09 03:18:02 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	err_backslash(void)
{
	ft_putstr_fd("Unclosed backslash\n", 2);
	return (1);
}

int	err_backtick(void)
{
	ft_putstr_fd("Unclosed backtick\n", 2);
	return (1);
}

// just if first, not handle rest
int	err_semicolon(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ';'\n", 2);
	return (1);
}

int	err_ampersand(char *s)
{
	int	i;

	i = 0;
	if (s[1] == '&')
		ft_putstr_fd("minishell: syntax error near unexpected token '&&'\n", 2);
	return (1);
}

int	err_curly(void)
{
	ft_putstr_fd("Unclosed curly brackets\n", 2);
	return (1);
}
