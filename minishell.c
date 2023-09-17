/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:09:47 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/31 16:21:52 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exitstatus = 0;

void	free_var(t_vars *var)
{
	int	i;

	i = 0;
	if (var->pipe_hrd != NULL)
		free(var->pipe_hrd);
	if (var->pipe_out != NULL)
		free(var->pipe_out);
	if (var->pipe_in != NULL)
		free(var->pipe_in);
	if (var->pipe != NULL)
		free(var->pipe);
	if (var->pid != NULL)
		free(var->pid);
	if (var->hrd_line != NULL)
		free(var->hrd_line);
	if (var->line_read != NULL)
		free(var->line_read);
}

void	ft_reset_fd(t_vars **var, t_creat **res, t_creat **list)
{
	ft_close_all_rd(*var);
	dup2((*var)->og_in, 0);
	dup2((*var)->og_out, 1);
	close((*var)->og_in);
	close((*var)->og_out);
	close((*var)->out);
	close((*var)->in);
	close((*var)->hd_pipe[0]);
	close((*var)->hd_pipe[1]);
	free_var(*var);
	free_list(res);
	free_list(list);
}

void	handler(int a)
{
	if (a != 3)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0); 
		rl_redisplay();
		g_exitstatus = 1;
	}
}

void	signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_creat	*res;
	t_creat	*list;
	t_vars	*var;
	t_env	*envr;

	(void)av;
	if (ac != 1)
		return (1);
	ft_init_s(&res, &var, &envr, &list);
	fill_env(&envr, env, 0, 0);
	while (1)
	{
		init_vars(var);
		signals();
		var->line_read = readline("minishell$ ");
		if (var->line_read == NULL)
			ft_exit_p(g_exitstatus);
		res = read_string(&list, var->line_read, envr);
		if (free_line(var->line_read))
			continue ;
		add_history(var->line_read);
		if (res != NULL)
			execute_cmd(&var, &envr, &res);
		ft_reset_fd(&var, &res, &list);
	}
}
