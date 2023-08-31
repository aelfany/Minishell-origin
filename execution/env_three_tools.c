/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_three_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:18:53 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/27 12:24:40 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_node(t_env *env, char *name, char *value, int i)
{
	t_env	*ptr;

	ptr = env;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = malloc(sizeof(t_env) * 1);
	ptr = ptr->next;
	ptr->name = ft_strdup1(ptr->name, name);
	ptr->value = ft_strdup1(ptr->name, value);
	ptr->uninitialized = i;
	ptr->hidden_flag = 0;
	ptr->next = NULL;
}

// THIS FUNCION RECHECKS IF OLDPWD OR SHLVL HAVE BEEN CREATED
// ADD OLDPWD IF IT DOSENT EXIST SET VALUE TO NULL;
// ADD SHLVL AND SET IT TO 1

void	ft_recheck(t_env *envr)
{
	t_env	*ptr;
	int		f;
	int		s;

	ptr = envr;
	f = 0;
	s = 0;
	while (ptr)
	{
		if (strcmp(ptr->name, "OLDPWD") == 0)
			f = 1;
		if (strcmp(ptr->name, "SHLVL") == 0)
			s = 1;
		ptr = ptr->next;
	}
	ptr = envr;
	if (f == 0)
		ft_add_node(ptr, "OLDPWD", NULL, 1);
	ptr = envr;
	if (s == 0)
		ft_add_node(ptr, "SHLVL", "1", 0);
}

// SET OLDPWD VALUE TO NULL IF  EXISTS
// SET SHLVL TO ONE IF IT HAS ANYTHING BUT NUMBERS OR EMPTY 
// ELSE IT ADD ONE TO IT 

static	void	shlvl_update(t_env **ptr)
{
	unsigned long long	num;

	num = 0;
	if ((*ptr)->value != NULL)
	{
		if (ft_isnum((*ptr)->value) == -1)
		{
			free((*ptr)->value);
			(*ptr)->value = ft_strdup1((*ptr)->value, "1");
		}
		else
		{
			num = ft_atoi((*ptr)->value, 0, (*ptr)) + 1;
			free((*ptr)->value);
			(*ptr)->value = ft_itoa(num);
		}
	}
}

void	ft_update_three(t_env *ptr)
{
	if (ft_strcmp(ptr->name, "OLDPWD") == 0)
	{
		if (ptr->value != NULL)
			free(ptr->value);
		ptr->value = NULL;
		ptr->uninitialized = 1;
	}
	if (ft_strcmp(ptr->name, "SHLVL") == 0)
		shlvl_update(&ptr);
}

// ADD SHLVL AND SET IT TO ONE IF IT DOSENT EXIST

void	ft_add_three(t_env **envr)
{
	t_env	*ptr;

	ptr = *envr;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "OLDPWD") == 0)
			ft_update_three(ptr);
		if (ft_strcmp(ptr->name, "SHLVL") == 0)
			ft_update_three(ptr);
		ptr = ptr->next;
	}
	ptr = *envr;
	if (ptr)
		ft_recheck(ptr);
	ptr = *envr;
}
