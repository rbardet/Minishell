/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:18:54 by throbert          #+#    #+#             */
/*   Updated: 2025/02/28 18:22:12 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_n_flag(char *s)
{
	int	i;

	i = 1;
	if (s[0] == '-' && s[1] == 'n')
	{
		while (s[i] != '\0' && s[i] == 'n')
			i++;
		if (s[i] == '\0')
			return (1);
	}
	return (0);
}

static void	echo_loop(char **cmd, int i)
{
	while (cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
		i++;
	}
}

// i goes forward just on flags
t_shell	*ft_echo(char **cmd, t_shell *shell)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	i = 1;
	shell->exit_code = 0;
	while (cmd[i] && is_valid_n_flag(cmd[i]))
	{
		no_newline = 1;
		i++;
	}
	echo_loop(cmd, i);
	if (!no_newline)
		ft_printf("\n");
	return (shell);
}
