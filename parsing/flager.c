/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   flager.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:39:05 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/24 23:13:29 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_quots(char *str, int *singl_quot)
{
	int	double_quot;

	double_quot = 0;
	while (*str)
	{
		if (*str == '"')
			double_quot++;
		if (*str == '\'')
			(*singl_quot)++;
		str++;
	}
	return (double_quot);
}

char	*take_word(char *cmd)
{
	int	singl_quot;
	int	double_quot;

	singl_quot = 0;
	double_quot = count_quots(cmd, &singl_quot);
	return (NULL);
}
