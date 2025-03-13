/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:50:47 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 16:04:40 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// close every fd and free all char * if STDIN is close or EOF is
// encountered.
void	close_all(char *str, char *limiter, int fd, t_shell *shell)
{
	close(shell->save_out);
	close(shell->save_in);
	if (str)
		free(str);
	if (limiter)
		free(limiter);
	get_next_line(-1);
	if (fd > 0)
		close(fd);
}

// here_doc loop that play until the LIMITER is typed in the terminal
static void	handle_flex(t_doc *doc)
{
	char	*flex;

	flex = ft_strdup(doc->limiter);
	flex[ft_strlen(flex) - 1] = '\0';
	ft_putstr_fd(flex, 2);
	free(flex);
}

static void	handle_doc_error(t_shell *shell, t_doc *doc, int fd)
{
	if (g_signal == SIGINT)
	{
		close_all(doc->str, doc->limiter, fd, shell);
		free(doc);
		free_all(shell, NULL);
		exit(130);
	}
	if (doc->str == NULL)
	{
		ft_putstr_fd("Minishell: warning: here_document", 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		handle_flex(doc);
		ft_putstr_fd("')\n", 2);
		close_all(doc->str, doc->limiter, fd, shell);
		free(doc);
		free_all(shell, NULL);
		exit(EXIT_SUCCESS);
	}
	if (ft_strncmp(doc->str, doc->limiter, ft_strlen(doc->str)) == 0)
	{
		close_all(doc->str, doc->limiter, fd, shell);
		free(doc);
		free_all(shell, NULL);
		exit(EXIT_SUCCESS);
	}
}

// here_doc loop that play until the LIMITER is typed in the terminal
void	here_doc(t_shell *shell, char **cmd, int i, char *file)
{
	t_doc	*doc;
	int		fd;

	doc = malloc(sizeof(t_doc));
	setup_signals2(2);
	fd = open(file, O_CREAT | O_RDWR, 0777);
	free(file);
	doc->limiter = ft_strjoin(cmd[i + 1], "\n");
	free_tab(cmd);
	if (fd < 0)
	{
		close_all(NULL, doc->limiter, fd, shell);
		free(doc);
		free_all(shell, NULL);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		doc->str = get_next_line(0);
		handle_doc_error(shell, doc, fd);
		ft_putstr_fd(doc->str, fd);
		free(doc->str);
	}
	return ;
}

int	handle_doc(t_shell *shell, int i, char **cmd, char **toks)
{
	pid_t	pid;
	char	*file;
	char	*tmp2;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	tmp2 = ft_itoa(shell->doc_count);
	file = ft_strjoin(".heredoc", tmp2);
	free(tmp2);
	if (pid == 0)
	{
		free_tab(toks);
		here_doc(shell, cmd, i, file);
	}
	free(file);
	return (wait_ignore(pid));
}
