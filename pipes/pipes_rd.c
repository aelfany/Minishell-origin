/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_rd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:50:05 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/21 23:15:58 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_find_last_rd_help(t_creat **ptr, t_vars *var, int i)
{
	if (i == 0)
	{
		if (var->p_in != -2)
		{
			close(var->p_in);
			var->p_in = -2;
		}
		if (var->p_in != -1)
			var->p_in = rd_in_p(ptr);
	}
	if (i == 1)
	{
		if (var->p_out != -2)
		{
			close(var->p_out);
			var->p_out = -2;
		}
		if (var->p_out != -1 && ft_strcmp((*ptr)->token, "RDOUT") == 0)
			var->p_out = rd_out_p(ptr);
		if (var->p_out != -1 && ft_strcmp((*ptr)->token, "RD_AP") == 0)
			var->p_out = rd_ap_p(ptr);
	}
}

int	ft_find_last_rd(t_creat **ptr, t_vars *var)
{
	int	i;

	i = 0;
	var->p_in = -2;
	var->p_out = -2;
	while ((*ptr) && ft_strcmp((*ptr)->token, "PIP") != 0)
	{
		if (ft_strcmp((*ptr)->token, "RDIN") == 0)
			ft_find_last_rd_help(ptr, var, 0);
		if (ft_strcmp((*ptr)->token, "RDOUT") == 0
			|| ft_strcmp((*ptr)->token, "RD_AP") == 0)
			ft_find_last_rd_help(ptr, var, 1);
		(*ptr) = (*ptr)->next;
	}
	if (var->pipe_in[var->i] != -1)
		var->pipe_in[var->i] = var->p_in;
	if (var->pipe_out[var->i] != -1)
		var->pipe_out[var->i] = var->p_out;
	return (0);
}

void	rd_init(t_creat *res, t_vars *var)
{
	t_creat	*ptr;

	ptr = res;
	var->p_in = -2;
	var->p_out = -2;
	var->i = 0;
	while (ptr && var->i < var->cmd_count)
	{
		ft_find_last_rd(&ptr, var);
		if (ptr && ft_strcmp(ptr->token, "PIP") == 0)
			ptr = ptr->next;
		else if (!ptr)
			break ;
		var->i++;
		var->p_in = -2;
		var->p_out = -2;
	}
	ft_input_fix(&var, res);
	var->i = 0;
}
