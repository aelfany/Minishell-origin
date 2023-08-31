/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:17:49 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/27 13:36:10 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_all_rd(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->cmd_count)
	{
		close(var->pipe_hrd[i]);
		close(var->pipe_in[i]);
		close(var->pipe_out[i]);
		i++;
	}
}

void	ft_execone(int	*end, t_creat *res, t_env *envr, t_vars *var)
{
	if (var->pipe_out[var->i] == -1 || var->pipe_in[var->i] == -1)
	{
		ft_close_all_rd(var);
		close(end[1]);
		close(end[0]);
		g_exitstatus = 1;
		exit(1);
	}
	dup2(end[1], STDOUT_FILENO);
	close(end[1]);
	close(end[0]);
	if (var->pipe_out[var->i] != -2)
		dup2(var->pipe_out[var->i], STDOUT_FILENO);
	if (var->pipe_in[var->i] != -2)
		dup2(var->pipe_in[var->i], STDIN_FILENO);
	ft_close_all_rd(var);
	if (check_built_ins(res) == 1)
	{
		exec_built_ins(&envr, res, var);
		exit (g_exitstatus);
	}
	else
		ft_exec_pipe(envr, res, 0);
}

void	ft_execpipe(t_env *envr, t_creat *res, t_vars *var)
{
	if (var->pipe_out[var->i] == -1 || var->pipe_in[var->i] == -1)
	{
		ft_close_all_rd(var);
		close(var->pipe[var->i - 1][1]);
		close(var->pipe[var->i - 1][0]);
		close(var->pipe[var->i][1]);
		close(var->pipe[var->i][0]);
		exit(1);
	}
	dup2(var->pipe[var->i - 1][0], STDIN_FILENO);
	dup2(var->pipe[var->i][1], STDOUT_FILENO);
	if (var->pipe_out[var->i] != -2)
		dup2(var->pipe_out[var->i], STDOUT_FILENO);
	if (var->pipe_in[var->i] != -2)
		dup2(var->pipe_in[var->i], STDIN_FILENO);
	ft_close_all_rd(var);
	if (check_built_ins(res) == 1)
	{
		exec_built_ins(&envr, res, var);
		exit (g_exitstatus);
	}
	else
		ft_exec_pipe(envr, res, 0);
}

void	ft_exectwo(int *end, t_creat *res, t_env *envr, t_vars *var)
{
	if (var->pipe_out[var->i] == -1 || var->pipe_in[var->i] == -1)
	{
		ft_close_all_rd(var);
		close(end[0]);
		close(end[1]);
		exit(1);
	}
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	close(end[1]);
	if (var->pipe_out[var->i] != -2)
		dup2(var->pipe_out[var->i], STDOUT_FILENO);
	if (var->pipe_in[var->i] != -2)
		dup2(var->pipe_in[var->i], STDIN_FILENO);
	ft_close_all_rd(var);
	if (check_built_ins(res) == 1)
	{
		exec_built_ins(&envr, res, var);
		exit (g_exitstatus);
	}
	else
		ft_exec_pipe(envr, res, 0);
}
