/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:16:23 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/23 09:51:20 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_first(int end[][2], t_creat *res, t_vars *var, t_env *envr)
{
	int	d;

	d = 0;
	while (d < var->pipe_count)
	{
		if (d == 0)
			close(end[d][0]);
		else
		{
			close(end[d][0]);
			close(end[d][1]);
		}
		d++;
	}
	ft_execone(end[var->i], res, envr, var);
}

void	ft_close_last(int end[][2], t_creat *res, t_vars *var, t_env *envr)
{
	int	d;

	d = 0;
	while (d < var->pipe_count)
	{
		if (d == var->pipe_count -1)
			close(end[d][1]);
		else
		{
			close(end[d][1]);
			close(end[d][0]);
		}
		d++;
	}
	ft_exectwo(end[var->i - 1], res, envr, var);
}

void	ft_close_pipe(int end[][2], t_creat *res, t_vars *var, t_env *envr)
{
	int	d;

	d = 0;
	while (d < var->pipe_count)
	{
		if (d == (var->i - 1))
			close(end[d][1]);
		else if (d == var->i)
			close(end[d][0]);
		else
		{
			close(end[d][0]);
			close(end[d][1]);
		}
		d++;
	}
	ft_execpipe(envr, res, var);
}

void	ft_close_all_p(t_vars *var, int i)
{
	int	d;

	d = 0;
	while (d < var->pipe_count)
	{
		close(var->pipe[d][0]);
		close(var->pipe[d][1]);
		d++;
	}
	if (i == 1)
		exit(0);
}
