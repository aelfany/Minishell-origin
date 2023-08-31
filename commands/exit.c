/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:01:52 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/28 14:33:05 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_error(char *str, int flag, t_env *envr)
{
	(void)envr;
	if (flag == 0)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exitstatus = 255;
		exit(255);
	}
	else if (flag == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		g_exitstatus = 1;
	}
}

static	int	ft_parser(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (-1);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] == '\0')
			return (-1);
		if (str[i] && (str[i] == '-' || str[i] == '+'))
			i++;
		while (str[i])
		{
			if (str[i] && (str[i] >= 48 && str[i] <= 57))
				i++;
			else
				return (-1);
		}
		if (str[i])
			i++;
	}
	return (0);
}

//checks first arg if numeric and has more args
// its too many args and dosent quit

//if its none numeric its args required and exits

static int	exit_parser(char **opt, int flag, int i, t_env *envr)
{
	if (opt[1] && flag == 0)
	{
		if (ft_parser(opt[1]) == -1)
			ft_exit_error(opt[1], 0, envr);
	}
	else if (flag == 1)
	{
		while (opt[i]) 
			i++;
		if (i > 2)
		{
			ft_exit_error(opt[1], 1, NULL);
			return (-1);
		}
	}
	return (0);
}

int	ft_exit(t_env *env, t_creat *res, t_vars *var)
{
	int	exitcode;

	exitcode = g_exitstatus;
	if (exit_parser(res->opt, 0, 0, env) == -1)
		exitcode = g_exitstatus;
	else if (exit_parser(res->opt, 1, 0, env) == -1)
		return (1);
	else if (res->opt[1])
		exitcode = (unsigned char)ft_atoi(res->opt[1], 0, env);
	else
		exitcode = g_exitstatus;
	printf("exit\n");
	free_var(var);
	exit(exitcode);
}
