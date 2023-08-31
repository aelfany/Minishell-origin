/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:19:21 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/27 22:58:55 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// for errors

static int	ft_error_cd(int n, t_creat *res)
{
	if (n == 0)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (n == 1)
	{
		if (!res->opt[1])
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(": No arguments\n", 2);
			return (n);
		}
		ft_putstr_fd("minishell: cd: ", 2);
		perror(res->opt[1]);
	}
	return (n);
}

//updates pwd if getcwd fails it displays the deleted dir msg

static int	ft_find_pwd(t_env **envr, t_creat *res)
{
	t_env	*ptr;
	char	*getcwds;

	ptr = *envr;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "PWD") == 0)
		{
			getcwds = getcwd(NULL, 0); 
			if (getcwds == NULL)
			{
				ft_error_cd(0, res);
				ptr->value = ft_strjoin_free(ptr->value, "/", 1, 0);
				ptr->value = ft_strjoin_free(ptr->value, res->opt[1], 1, 0);
				break ;
			}
			free(getcwds);
			free(ptr->value);
			ptr->value = getcwd(NULL, 0);
			break ;
		}
		ptr = ptr->next;
	}
	return (0);
}

//updates 1pwd if getcwd fails it displays the deleted dir msg
// which is a hidden var used by pwd to never fail

static int	ft_find_1pwd(t_env **envr, t_creat *res)
{
	t_env	*ptr;
	char	*getcwds;

	ptr = *envr;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "1PWD") == 0)
		{
			getcwds = getcwd(NULL, 0);
			if (getcwds == NULL)
			{
				ptr->value = ft_strjoin_free(ptr->value, "/", 1, 0);
				ptr->value = ft_strjoin_free(ptr->value, res->opt[1], 1, 0);
				break ;
			}
			free(getcwds);
			free(ptr->value);
			ptr->value = getcwd(NULL, 0);
			break ;
		}
		ptr = ptr->next;
	}
	return (0);
}

// -- if (ft_strcmp(ptr->name, "PWD") == 0) 
// if pwd exists add it to oldpwd before its changed 
//	-- if (chdir(res->opt[1]) == -1) 
//change dir if fails display error msg not found
//  -- flag = ft_find_pwd(envr, res); 
//updates the pwd and  checks if the deleted dir error is detected

int	cd(t_creat *res, t_env **envr, int flag)
{
	t_env	*ptr; 

	ptr = *envr;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "PWD") == 0)
		{
			ft_add_oldpwd(envr, ptr->value);
			break ;
		}
		else if (ft_strcmp(ptr->name, "OLDPWD") == 0)
			ft_add_oldpwd(envr, NULL);
		ptr = ptr->next;
	}
	if (chdir(res->opt[1]) == -1)
	{
		flag = ft_error_cd(1, res);
		return (flag);
	}
	flag = ft_find_pwd(envr, res);
	ft_find_1pwd(envr, res);
	return (flag);
}
