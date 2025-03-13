/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:12:37 by throbert          #+#    #+#             */
/*   Updated: 2025/03/08 16:17:22 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	sig_handler(int signum)
{
	g_signal = signum;
	if (g_signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals(int mode)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	if (mode == 1)
	{
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = sig_handler;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGTSTP, &sa, NULL);
	}
	else if (mode == 0)
	{
		sa.sa_handler = SIG_DFL;
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGTSTP, &sa, NULL);
	}
}

void	wait_pid_ignore_signals(pid_t pid, int *exit_code)
{
	struct sigaction	ignore_sig;
	struct sigaction	old_sigint;
	struct sigaction	old_sigquit;

	ignore_sig.sa_handler = SIG_IGN;
	sigemptyset(&ignore_sig.sa_mask);
	ignore_sig.sa_flags = 0;
	sigaction(SIGINT, &ignore_sig, &old_sigint);
	sigaction(SIGQUIT, &ignore_sig, &old_sigquit);
	waitpid(pid, exit_code, WUNTRACED);
	sigaction(SIGINT, &old_sigint, NULL);
	sigaction(SIGQUIT, &old_sigquit, NULL);
}

int	wait_ignore(pid_t pid)
{
	int	exit_code;

	if (pid == 0)
		return (0);
	if (pid == 1)
		return (1);
	wait_pid_ignore_signals(pid, &exit_code);
	if (WIFSTOPPED(exit_code))
	{
		g_signal = WSTOPSIG(exit_code);
		ft_putstr_fd("\n[1]+  Stopped\n", STDERR_FILENO);
	}
	else if (WIFSIGNALED(exit_code))
	{
		g_signal = WTERMSIG(exit_code);
		if (g_signal == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		else if (g_signal == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (128 + g_signal);
}
