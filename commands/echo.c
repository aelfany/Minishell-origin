/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:53:34 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/23 11:32:15 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	new_line_checker(char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "-n") == 0)
		return (0);
	else if (str[i] == '-')
	{
		i++;
		if (str[i] == '\0')
			return (1);
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (0);
		else
			return (1);
	}
	return (1);
}

static int	echo_helper(char **opt, int flag, int i)
{
	int	d;

	d = 0;
	while (opt[i] && new_line_checker(opt[i]) == 0)
	{
		i++;
		flag = 1;
	}
	while (opt[i])
	{
		while (opt[i][d])
		{
			write(1, &opt[i][d], 1);
			d++;
		}
		d = 0;
		i++;
		if (opt[i])
			write(1, " ", 1);
	}
	return (flag);
}

int	echo(char **opt)
{
	int		flag;

	flag = 0;
	if (!opt[1])
	{
		printf("\n");
		return (0);
	}
	flag = echo_helper(opt, flag, 1);
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
