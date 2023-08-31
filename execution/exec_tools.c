/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:01:44 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/28 22:07:21 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_size(t_env *ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "1PWD") == 0)
		{
			ptr = ptr->next;
			continue ;
		}
		ptr = ptr->next;
		i++;
	}
	return (i);
}

int	ft_file_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		if (cmd[0] == '/')
			return (-1);
		if (cmd[0] == '.' && cmd[1] == '/')
			return (-1);
		if ((cmd[0] == '.' && cmd[1] == '.' ) && cmd[2] == '/')
			return (-1);
	}
	return (0);
}

char	*command_finder(char *cmd, char *env, int i)
{
	char	**path;
	char	*fullcmd;

	path = ft_split(env, ':');
	fullcmd = NULL;
	if (access(cmd, X_OK) == 0 || ft_file_check(cmd) == -1)
	{
		ft_free_loop(path);
		return (cmd);
	}
	if (env == NULL || cmd[0] == ' ' || cmd[0] == '\t')
		return (free_path(path));
	while (path[i++])
	{
		fullcmd = ft_strjoin_free(path[i], "/", 0, 0);
		fullcmd = ft_strjoin_free(fullcmd, cmd, 1, 0);
		if (access(fullcmd, X_OK) == 0)
		{
			ft_free_loop(path);
			return (fullcmd);
		}
		free (fullcmd);
	}
	ft_free_loop(path);
	return (cmd);
}

void	exec_built_ins(t_env **envr, t_creat *res, t_vars *var)
{
	if (ft_strcmp(res->cmd, "cd") == 0)
		g_exitstatus = cd(res, envr, 0);
	else if (ft_strcmp(res->cmd, "echo") == 0)
		g_exitstatus = echo(res->opt);
	else if (ft_strcmp(res->cmd, "pwd") == 0)
		g_exitstatus = pwd(*envr);
	else if (ft_strcmp(res->cmd, "export") == 0)
		ft_export(envr, res->opt, 1);
	else if (ft_strcmp(res->cmd, "unset") == 0)
		unset(envr, res, 1);
	else if (ft_strcmp(res->cmd, "env") == 0)
		ft_env(res->opt, *envr);
	else if (ft_strcmp(res->cmd, "exit") == 0)
		ft_exit(*envr, res, var);
}

void	execute_cmd(t_vars **var, t_env **envr, t_creat **res)
{
	t_creat	*ptr;

	ptr = *res;
	ft_init_p_vars(*var, *res);
	if (check_pipes(*res) == 1)
	{
		pipes_exec(*res, *var, *envr);
		return ;
	}
	if (ft_open_heredocs(res, var, *envr) == 1)
		return ;
	ft_open_redirections(res, var);
	while (ptr)
	{
		if ((*var)->failed_rd == -1)
			break ;
		else if (ft_strcmp(ptr->token, "CMD") == 0)
		{
			if (check_built_ins(*res) == 1)
				exec_built_ins(envr, ptr, *var);
			else
				ft_exec(*envr, *res);
		}
		ptr = ptr->next;
	}
}
