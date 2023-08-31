/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:33:34 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/26 18:18:09 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//fills up the value

void	ft_fillup_envr(t_env *ptr, char *env)
{
	int	i;
	int	d;

	d = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] == '=')
		i++;
	while (env[i])
	{
		ptr->value[d] = env[i];
		i++;
		d++;
	}
	ptr->value[d] = '\0';
	ptr->hidden_flag = 0;
	ptr->next = NULL;
}

//fills up the id name

void	ft_fillup(t_env *ptr, char *env)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (env[i] != '=' && env[i])
	{
		if (env[i] == '+')
		{
			i++;
			continue ;
		}
		ptr->name[d] = env[i];
		i++;
		d++;
	}
	ptr->name[d] = '\0';
	ptr->hidden_flag = 0;
	ptr->value = NULL;
	ptr->next = NULL;
}

// -ft_fillup  = fills up name
// -if (ft_strcmp(ptr->name, "OLDPWD") == 0)
// if equals oldpwd skip it ps : it gets created until cd is used
// -ft_fillup_envr(ptr, env[i]); = filling up  the value of name
// -if (env[i + 1]) = checks if env is still going 

// fills up env list

void	ft_env_helper(t_env **ptr, char **env, int i)
{
	if (env[i + 1])
	{
		(*ptr)->next = malloc(sizeof(t_env) * 1);
		ft_malloc_protect((*ptr)->next);
		(*ptr) = (*ptr)->next;
	}
	else
		(*ptr)->next = NULL;
}

static void	skip_env(int *i, char *name)
{
	(*i)++;
	free(name);
}

void	fill_env(t_env **envr, char **env, int d, int i)
{
	t_env	*ptr;

	ptr = *envr;
	if (check_env_unavailable(envr, env[0]) == 1)
		return ;
	while (env[i])
	{
		d = calc_size(env[i], '=');
		ptr->name = malloc(1 * d + 1);
		ft_malloc_protect(ptr->name);
		ft_fillup(ptr, env[i]);
		if (ft_strcmp(ptr->name, "1PWD") == 0)
		{
			skip_env(&i, ptr->name);
			continue ;
		}
		ptr->value = malloc(1 * (ft_strlen(env[i]) - d) + 1);
		ft_malloc_protect(ptr->value);
		ft_fillup_envr(ptr, env[i]);
		ft_env_helper(&ptr, env, i);
		i++;
	}
	add_1pwd(ptr);
	ptr = *envr;
	ft_add_three(&ptr);
}
