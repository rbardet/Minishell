/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:52:41 by throbert          #+#    #+#             */
/*   Updated: 2025/03/13 19:28:21 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	err_bracket(char *s)
{
	if (s[0] == '[' && s[1] == '\0')
		ft_putstr_fd("Unclosed brackets\n", 2);
	else if (s[0] == '[' && s[1] == '[' && s[2] == '\0')
		ft_putstr_fd("minishell: [: missing `]'\n", 2);
	return (1);
}

int	err_percent(char *s)
{
	ft_putstr_fd("minishell: fg: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": no such job\n", 2);
	return (1);
}

int	err_type_utils(char *s, char sym)
{
	if (check_par(s) == 1)
		return (err_par(sym));
	else if (check_par(s) == 2)
		return (new_line_err());
	return (0);
}

int	error_type(char *s, char sym)
{
	if (sym == '(')
		return (err_type_utils(s, sym));
	else if (sym == ')')
		return (err_par(sym));
	else if (sym == ';')
		return (err_semicolon());
	else if (sym == '&')
		return (err_ampersand(s));
	else if (sym == '|')
	{
		if (s[0] == '|')
			return (err_pipe(s));
	}
	else if (sym == '{' && s[1] == '\0')
		return (err_curly());
	else if (sym == '}' && s[1] == '\0')
		return (err_curly2());
	else if (sym == '[' && (s[1] == '\0' || (s[1] == '[' && s[2] == '\0')))
		return (err_bracket(s));
	else if (sym == '%')
		return (err_percent(s));
	return (0);
}

int	check_error_token(char *s)
{
	if (!s || !*s)
		return (0);
	if (s[0] == ';' || (s[0] == '&' && s[1] == '&') || s[0] == '|'
		|| s[0] == '(' || s[0] == '{' || s[0] == '['
		|| s[0] == '%' || s[0] == '}' || s[0] == ')')
	{
		if (error_type(s, s[0]))
			return (1);
	}
	return (0);
}
