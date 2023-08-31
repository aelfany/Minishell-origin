/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:21:22 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/27 12:22:03 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_strlen_delim(char *str, char delim)
{
	int	i;

	i = 0;
	while (str[i] != delim && str[i])
		i++;
	return (i);
}

int	calc_size(char *str, char delim)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (str[i])
	{
		if (str[i] == '+')
			d = 1;
		if (str[i] == delim)
			return (i);
		i++;
	}
	i = i - d;
	return (i);
}
