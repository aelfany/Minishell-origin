/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:39:22 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/23 10:21:50 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_symbols(char *env, int i)
{
	int	flag;

	flag = -1;
	if (env[0] == '\0' || env[0] == '+' || env[0] == '=')
		return (-1);
	while (env[i] && env[i] != '=')
	{
		if (((env[i] >= 97 && env[i] <= 122) || (env[i] >= 65 && env[i] <= 90)))
			flag = 0;
		else if ((env[i] >= 48 && env[i] <= 57))
			flag = 0;
		else if (env[i] == '_')
			flag = 0;
		else if (env[i] == '+' && env[i + 1] == '=')
			flag = 0;
		else
			break ;
		i++;
	}
	if (env[i] == '\0' || env[i] == '=')
		return (0);
	if (env[i] != '=')
		return (-1);
	return (0);
}

//counts for the + signs parsing 

int	append_count(char *env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[i] != '=' && env[i])
	{
		if (env[i] == '+')
			count++;
		i++;
	}
	if (count > 1)
		return (-1);
	i = 0;
	while (env[i] != '=' && env[i])
	{
		if (env[i] == '+' && env[i + 1] != '=')
			return (-1);
		i++;
	}
	return (0);
}

static int	ft_helper(char *env, int n, int i)
{
	int	flag;

	flag = 0;
	while (env[i] && env[i] != '=')
	{
		if (env[i] == ' ' || env[i] == '\t')
			return (-1);
		i++;
	}
	if ((env[0] >= 48 && env[0] <= 57))
		flag = -1;
	else if (append_count(env) == -1 && n == 0)
		flag = -1;
	else if (ft_check_symbols(env, 0) == -1)
		flag = -1;
	return (flag);
}

int	ft_count_vars(char **opt, t_env *envr)
{
	int	i;

	i = 1;
	while (opt[i])
		i++;
	if (i == 1)
	{
		print_env(envr);
		g_exitstatus = 0;
	}
	return (i);
}

int	ft_export_parser(char *env, int n)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (n == 0)
		flag = ft_helper(env, n, i);
	else if (n == 1)
		flag = ft_unset_parser(env);
	if (flag == -1 && n == 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(env, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		g_exitstatus = 1;
	}
	else if (flag == -1 && n == 1)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(env, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		g_exitstatus = 1;
	}
	return (flag);
}
