/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:27:56 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/28 20:56:34 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**fillup_exec_env(t_env *envr, int i)
{
	t_env	*ptr;
	char	**env;

	ptr = envr;
	env = NULL;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	ptr = envr;
	env = malloc(sizeof(char *) * (i + 1));
	ft_malloc_protect(env);
	i = 0;
	while (ptr)
	{
		env[i] = ft_strjoin(ptr->name, "=");
		env[i] = ft_strjoin(env[i], ptr->value);
		i++;
		ptr = ptr->next;
	}
	env[i] = NULL;
	return (env);
}

static void	ft_execute_help(char *cmd, char **opt, char **env, t_creat *res)
{
	if (execve(cmd, opt, env) == -1)
	{
		ft_error_exec(res, cmd, 1);
	}
}

void	ft_exec_pipe(t_env *envr, t_creat *res, int i)
{
	char	**env;
	char	*cmd;
	t_env	*ptr;

	ptr = envr;
	env = fillup_exec_env(envr, 0);
	cmd = NULL;
	if (res->cmd[0])
		cmd = command_finder(res->cmd, my_get_env(envr, "PATH"), 0);
	if (cmd == NULL)
	{
		ft_error_exec(res, res->cmd, 0);
		g_exitstatus = 127;
		exit(127);
	}
	ft_execute_help(cmd, res->opt, env, res);
	i = 0;
	while (env[i++])
		free(env[i]);
}
