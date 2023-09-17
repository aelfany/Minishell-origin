/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:00:16 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/31 16:16:41 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isoverflow(int sign)
{
	if (sign == -1)
		return (0);
	else
		return (-1);
}

unsigned long long	ft_atoi(char *str, size_t i, t_env *envr)
{
	unsigned long long	result;
	unsigned long long	prev;
	int					sign;

	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = result;
		result = result * 10 + (str[i] - '0');
		if ((result / 10) != prev)
			ft_exit_error(str, 0, envr);
		i++;
	}
	return (result * sign);
}
