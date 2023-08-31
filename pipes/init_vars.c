/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 21:43:59 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/28 14:46:43 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// function that inits all variables needed by pipes

void	ft_init_p_vars(t_vars *var, t_creat *res)
{
	t_creat	*ptr;

	ptr = res;
	pipe_calc(res, var);
	var->i = 0;
	var->pid = malloc(sizeof(int *) * var->cmd_count);
	ft_malloc_protect(var->pid);
	var->pipe = malloc(sizeof(int *) * var->pipe_count);
	ft_malloc_protect(var->pipe);
	var->pipe_in = malloc(sizeof(int) * var->cmd_count);
	ft_malloc_protect(var->pipe_in);
	var->pipe_out = malloc(sizeof(int) * var->cmd_count);
	ft_malloc_protect(var->pipe_out);
	var->pipe_hrd = malloc(sizeof(int) * var->cmd_count);
	ft_malloc_protect(var->pipe_hrd);
	while (var->i < var->cmd_count)
	{
		var->pipe_out[var->i] = -2;
		var->pipe_in[var->i] = -2;
		var->pipe_hrd[var->i] = -2;
		var->i++;
	}
	var->i = 0;
}
