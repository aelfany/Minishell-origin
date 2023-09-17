/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:27:15 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/31 18:36:26 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	if (g_exitstatus == 2) // cmd exited with ctl-c
//	if (g_exitstatus == 3) // cmd exited with ctl- backslash

void	ft_error_exec_help(t_creat *res, char *cmd, int flag)
{
	if (access(cmd, X_OK) != 0 && ft_file_check(cmd) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(res->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		if (flag == 1)
			exit(127);
	}
	else if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(res->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		if (flag == 1)
			exit(127);
	}
}

void	ft_error_exec(t_creat *res, char *cmd, int flag)
{
	int	i;
	DIR	*d;

	i = 0;
	d = opendir(cmd);
	if (d != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(res->cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		closedir(d);
		if (flag == 1)
			exit(126);
	}
	else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(res->cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		if (flag == 1)
			exit(126);
	}
	else
		ft_error_exec_help(res, cmd, flag);
}

static char	**fillup_exec_env(t_env *envr, int i)
{
	t_env	*ptr;
	char	**env;

	ptr = envr;
	env = NULL;
	i = ft_env_size(ptr);
	env = malloc(sizeof(char *) * (i + 1));
	ft_malloc_protect(env);
	i = 0;
	ptr = envr;
	while (ptr)
	{
		if (ptr && ft_strcmp(ptr->name, "1PWD") == 0)
		{
			ptr = ptr->next;
			continue ;
		}
		env[i] = ft_strjoin(ptr->name, "=");
		env[i] = ft_strjoin_free(env[i], ptr->value, 1, 0);
		i++;
		ptr = ptr->next;
	}
	env[i] = NULL;
	i = 0;
	return (env);
}

void	ft_execute_help(char *cmd, char **opt, t_env *envr, t_creat *res)
{
	int		p_id;
	int		status;
	char	**env;

	env = NULL;
	p_id = fork();
	ft_systemcall_protect(p_id);
	if (p_id != 0)
		signal_ignore();
	if (p_id == 0)
	{
		signal_child();
		env = fillup_exec_env(envr, 0);
		if (execve(cmd, opt, env) == -1)
		{
			ft_free_loop(env);
			ft_error_exec(res, cmd, 1);
		}
	}
	waitpid(p_id, &status, 0);
	exitstatus_handler(status);
	signals();
}

void	ft_exec(t_env *envr, t_creat *res)
{
	char	*cmd;
	t_env	*ptr;

	ptr = envr;
	cmd = NULL;
	if (res->cmd[0])
		cmd = command_finder(res->cmd, my_get_env(envr, "PATH"), 0);
	if (cmd == NULL)
	{
		ft_error_exec(res, res->cmd, 0);
		g_exitstatus = 127;
		return ;
	}
	ft_execute_help(cmd, res->opt, envr, res);
	if (ft_strcmp(res->cmd, cmd) != 0)
		free(cmd);
}
