/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:50:08 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/28 14:36:09 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// initalizes the needed variables in the struct

void	init_vars(t_vars *var)
{
	var->line_read = NULL;
	var->hrd_line = NULL;
	var->pipe_in = NULL;
	var->pipe_out = NULL;
	var->pipe_hrd = NULL;
	var->pid = NULL;
	var->p_in = 0;
	var->p_out = 0;
	var->p_hrd = 0;
	var->failed_rd = 0;
	var->pipe_count = 0;
	var->cmd_count = 0;
	var->pipe = NULL;
	var->hd_pipe[0] = -2;
	var->hd_pipe[1] = -2;
	var->i = 0;
	var->redirections_bool = -1;
	var->og_in = -1;
	var->og_out = -1;
	var->in = -1;
	var->out = -1;
}

void	ft_init_s(t_creat **res, t_vars **var, t_env **envr, t_creat **list)
{
	*list = NULL;
	*res = NULL;
	*envr = malloc(sizeof(t_env) * 1);
	ft_malloc_protect(*envr);
	*var = malloc(sizeof(t_vars) * 1);
	ft_malloc_protect(*var);
}
