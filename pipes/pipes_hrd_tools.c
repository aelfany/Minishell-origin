/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_hrd_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 21:52:27 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/25 10:25:06 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	hrd_handler(int a)
{
	if (a == 2)
		exit(1);
	return ;
}

void	hrd_signal_reset(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, hrd_handler);
}
