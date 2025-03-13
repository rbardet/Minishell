/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 04:22:16 by throbert          #+#    #+#             */
/*   Updated: 2025/03/09 04:22:26 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	err_pipe(char *s)
{
	if (s[1] == '|')
		ft_putstr_fd("minishell: syntax error near unexpected token '||'\n", 2);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
	return (1);
}
