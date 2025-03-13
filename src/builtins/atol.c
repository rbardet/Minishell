/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:51:52 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/13 14:42:45 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*skip_whitespace_and_sign(char *str, int *sign)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		else
			*sign = 1;
		str++;
	}
	return (str);
}

static long long	convert_digits(char *str, int sign, int *error)
{
	long long	result;

	result = 0;
	while (*str)
	{
		if (!isdigit(*str))
		{
			*error = 1;
			return (0);
		}
		if ((result > LLONG_MAX / 10)
			|| (result == LLONG_MAX / 10
				&& (*str - '0') > (LLONG_MAX % 10 + (sign == -1))))
		{
			*error = 1;
			return (0);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

// a reproduction of atol but if it overflow the error count is set
// to 1 and returned.
long long	ft_atol_safe(char *str, int *error)
{
	int			sign;
	long long	result;

	sign = 1;
	*error = 0;
	str = (char *)skip_whitespace_and_sign(str, &sign);
	result = convert_digits(str, sign, error);
	return (sign * result);
}

int	ft(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}
