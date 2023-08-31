/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:04:33 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/23 09:48:40 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipes(t_creat *res)
{
	t_creat	*ptr;

	ptr = res;
	while (ptr)
	{
		if (ft_strcmp(ptr->token, "PIP") == 0)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	pipe_calc(t_creat *res, t_vars *var)
{
	t_creat	*ptr;

	ptr = res;
	var->pipe_count = 0;
	while (ptr)
	{
		if (ft_strcmp(ptr->token, "PIP") == 0)
			var->pipe_count++;
		ptr = ptr->next;
	}
	var->cmd_count = var->pipe_count + 1;
}

void	ft_pipe(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->pipe_count)
	{
		ft_systemcall_protect(pipe(var->pipe[i]));
		i++;
	}
}
