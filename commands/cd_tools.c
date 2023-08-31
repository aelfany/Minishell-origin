/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 00:05:50 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/27 22:01:07 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//updates oldpwd envr if dosent exist creates it

static void	old_pwd_helper(t_env **ptr, char *oldcwd)
{
	while ((*ptr)->next)
		(*ptr) = (*ptr)->next;
	(*ptr)->next = malloc(sizeof(t_env) * 1);
	ft_malloc_protect((*ptr)->next);
	(*ptr) = (*ptr)->next;
	(*ptr)->name = ft_strdup1((*ptr)->name, "OLDPWD");
	(*ptr)->value = ft_strdup1((*ptr)->value, oldcwd);
	(*ptr)->hidden_flag = 0;
	(*ptr)->next = NULL;
}

void	ft_add_oldpwd(t_env **envr, char *oldcwd)
{
	t_env	*ptr;

	ptr = *envr;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "OLDPWD") == 0)
		{
			free(ptr->value);
			if (oldcwd != NULL)
				ptr->value = ft_strdup1(ptr->value, oldcwd);
			else
			{
				ptr->uninitialized = 0;
				ptr->value = NULL;
			}
			return ;
		}
		ptr = ptr->next;
	}
	ptr = *envr;
	old_pwd_helper(&ptr, oldcwd);
}
