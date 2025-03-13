/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:52:11 by throbert          #+#    #+#             */
/*   Updated: 2025/03/13 20:47:40 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	validate_quotes_token(t_shell *shell, char *str)
{
	if (!all_quotes_closed(str))
		return (ft_putstr_fd("Unclosed quotes\n", 2),
			shell->exit_code = 2, 1);
	if (check_error_token(str))
		return (shell->exit_code = 2, 1);
	return (0);
}

// remove all baktick and verify if empty str=
// if there is quote " or ' " its not considered empty
static int	check_empty_trim(char *in, int h_single, int h_double)
{
	char	*temp_trim;
	int		result;

	temp_trim = ft_strtrim(in, "`");
	result = (!h_single && !h_double && temp_trim && !ft_strlen(temp_trim));
	free(temp_trim);
	return (result);
}

char	*validate_input(char *in, t_shell *shell)
{
	char	*processed_in;
	char	*final_in;
	int		has_quotes[2];

	has_quotes[0] = (ft_strlen(in) >= 2 && in[0] == '\''
			&& in[ft_strlen(in) - 1] == '\'');
	has_quotes[1] = (ft_strlen(in) >= 2 && in[0] == '"'
			&& in[ft_strlen(in) - 1] == '"');
	if (validate_quotes_token(shell, in)
		|| validate_only_backslash_tick(shell, in))
		return (ft_strdup(""));
	if (check_empty_trim(in, has_quotes[0], has_quotes[1]))
		return (ft_strdup(""));
	final_in = remove_empty_backticks(in);
	processed_in = parse_cmd(final_in);
	free(final_in);
	return (processed_in);
}
