/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:46:05 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/28 19:19:23 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_ignore(int a)
{
	if (a == 3)
		return ;
	else if (a != 3)
		return ;
	return ;
}

void	here_doc_handler(int a)
{
	if (a == 2)
		exit(1);
	return ;
}

void	exitstatus_handler(int status)
{
	if (WIFEXITED(status) != 0)
		g_exitstatus = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) != 0)
	{
		g_exitstatus = WTERMSIG(status);
		if (g_exitstatus == 2)
			g_exitstatus = 130;
		if (g_exitstatus == 3) 
			g_exitstatus = 131;
	}
}
