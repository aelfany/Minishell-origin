/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:59:47 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/28 17:47:35 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_wts(char c, char *wts)
{
	int	x;

	x = 0;
	while (wts[x])
	{
		if (c == wts[x])
			return (1);
		x++;
	}
	return (0);
}

int	not_string(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (0);
	return (1);
}

int	flag_fun(char *str, char x)
{
	while (*str)
	{
		if (*str == x)
			return (1);
		str++;
	}
	return (0);
}
