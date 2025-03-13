/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:29:56 by throbert          #+#    #+#             */
/*   Updated: 2025/02/26 04:50:28 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_signal = 2;
	close(STDIN_FILENO);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	setup_signals2(int mode)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	if (mode == 2)
	{
		sa.sa_handler = sigint_handler_heredoc;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
}
