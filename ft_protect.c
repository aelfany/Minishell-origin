/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_protect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:43:27 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/28 21:33:53 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_protect(void *ptr)
{
	if (!ptr)
	{
		perror("minishell: ");
		exit (-1);
	}
}

void	ft_systemcall_protect(int val)
{
	if (val == -1)
	{
		perror("minishell: ");
		exit (-1);
	}
}
