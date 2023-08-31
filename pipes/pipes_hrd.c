/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_hrd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:57:39 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/27 23:11:42 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//(*var)->hrd_line = ft_strjoin((*var)->hrd_line, "\n");
//expand right under this line

// SIGINT CTRL - C
// SIGQUIT CTRL - BACKSLASH
static void	heredoc_output(t_vars **var, t_env *envr, int flag)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	(*var)->hrd_line = ft_strjoin_free((*var)->hrd_line, "\n", 1, 0);
	while ((*var)->hrd_line[i])
	{
		if ((*var)->hrd_line[i] == '$' && flag == 0)
			res = ft_strjoin_free(res, expand_word((*var)->hrd_line, &i, envr), \
				1, 1);
		else if ((*var)->hrd_line[i] && (*var)->hrd_line[i] != '$' && flag == 0)
		{
			res = ft_charjoin(res, (*var)->hrd_line[i]);
			i++;
		}
		else
		{
			res = ft_charjoin(res, (*var)->hrd_line[i]);
			i++;
		}
	}
	ft_putstr_fd(res, (*var)->hd_pipe[1]);
	free(res);
}

static void	here_doc_hlp(t_vars **var, char *delim, t_env *envr, t_creat *res)
{
	int	flag;

	flag = ft_exp_check(res->token);
	while (1)
	{
		(*var)->hrd_line = readline("> ");
		if (ft_strcmp((*var)->hrd_line, delim) == 0)
		{
			free((*var)->hrd_line);
			exit(0);
		}
		else
			heredoc_output(var, envr, flag);
		free((*var)->hrd_line);
	}
}

static void	here_doc(t_creat **res, t_vars **var, t_env *envr, int status)
{
	int	id;

	if ((*var)->pipe_hrd[(*var)->i] != -2)
	{
		close((*var)->hd_pipe[0]);
		close((*var)->hd_pipe[1]);
	}
	else
	{
		(*var)->hd_pipe[0] = -2;
		close((*var)->hd_pipe[1]);
	}
	pipe((*var)->hd_pipe);
	signal_ignore();
	id = fork();
	ft_systemcall_protect(id);
	if (id == 0)
	{
		signal_hrd();
		close((*var)->hd_pipe[0]);
		here_doc_hlp(&(*var), (*res)->cmd, envr, *res);
	}
	waitpid(id, &status, 0);
	signals();
	g_exitstatus = WEXITSTATUS(status);
}

static void	ft_open_heredocs_p(t_creat **res, t_vars **var, t_env *envr)
{
	(*var)->p_hrd = -2; 
	while ((*res) && ft_strcmp((*res)->token, "PIP") != 0)
	{
		if (ft_check_hrd((*res)->token) == 0)
		{
			g_exitstatus = 0;
			close((*var)->p_hrd);
			here_doc(res, var, envr, 0);
			if (g_exitstatus == 1)
				return ;
			close((*var)->hd_pipe[1]);
			(*var)->p_hrd = (*var)->hd_pipe[0]; 
		}
		(*res) = (*res)->next;
	}
	(*var)->pipe_hrd[(*var)->i] = (*var)->p_hrd;
	return ;
}

int	ft_heredoc_p(t_creat *res, t_vars *var, t_env *envr)
{
	t_creat	*ptr;

	ptr = res;
	var->p_hrd = -2;
	var->i = 0;
	var->og_in = dup(0);
	var->og_out = dup(1);
	while (ptr && var->i < var->cmd_count)
	{
		ft_open_heredocs_p(&ptr, &var, envr);
		if (g_exitstatus == 1)
			return (1);
		if (ptr && ft_strcmp(ptr->token, "PIP") == 0)
		{
			ptr = ptr->next;
			var->i++;
			var->p_hrd = -2;
			continue ;
		}
		else if (!ptr)
			break ;
	}
	var->i = 0;
	ft_pipe(var);
	return (0);
}
