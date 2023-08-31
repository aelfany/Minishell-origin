/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:56:34 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/26 23:14:44 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// //checks if it needs to be appended if true returns 1

int	ft_check_append(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_append(t_env *ptr, char *str, int i)
{
	char	*append;
	char	*result;
	int		d;

	append = malloc(1 * (ft_strlen(str) - i) + 1);
	result = NULL;
	d = 0;
	while (str[i])
	{
		append[d] = str[i];
		d++;
		i++;
	}
	append[d] = '\0';
	result = ft_strjoin(ptr->value, append);
	if (ptr->value != NULL)
		free(ptr->value);
	if (append != NULL)
		free(append);
	ptr->value = result;
	ptr->uninitialized = 0;
	ptr->hidden_flag = 0;
	return (1);
}

//  -- if (str[i] == '\0')
//		return (1);  
// condition done for name that exists and cant be updated since
// there is no value EX: export a

int	ft_change_env(t_env *env_struct, char *str)
{
	int		i;
	int		d;

	i = ft_strlen_delim(str, '=');
	d = 0;
	if (str[i] == '\0')
		return (1);
	i++;
	if (ft_check_append(str) == 1 || env_struct->value == NULL)
		return (ft_append(env_struct, str, i));
	else
	{
		free(env_struct->value);
		env_struct->value = malloc(1 * (ft_strlen(str) - i) + 1);
	}
	while (str[i])
	{
		env_struct->value[d] = str[i];
		d++;
		i++;
	}
	env_struct->value[d] = '\0';
	env_struct->hidden_flag = 0;
	return (1);
}

// -- compares given name return 1 if there and updated else returns 0

int	ft_search_env(t_env **env_struct, char *str)
{
	t_env	*ptr;
	int		i;
	int		d;
	char	*str_id;

	i = 0;
	d = 0;
	str_id = ft_id_fillup(str);
	ptr = *env_struct;
	i = 0;
	while (ptr)
	{
		if (ft_strcmp(str_id, ptr->name) == 0)
		{
			i = ft_change_env(ptr, str);
			break ;
		}
		ptr = ptr->next;
	}
	free(str_id);
	return (i);
}

// -- ft_count_vars = counts how many options there is if none prints env
// -- ft_search_env = searches for the env if exists it changes or appends to it
// -- ft_export_last = adds the env variable to the list

void	ft_export(t_env **envr, char **opt, int d)
{
	t_env	*ptr;

	ptr = *envr;
	if (ft_count_vars(opt, *envr) == 1)
		return ;
	while (opt[d])
	{
		if (ft_export_parser(opt[d], 0) == -1) 
		{
			d++;
			continue ;
		}
		if (ft_search_env(envr, opt[d]) == 1)
		{
			d++;
			g_exitstatus = 0;
			continue ;
		}
		if (ft_export_last(envr, opt, d) == 1)
		{
			d++;
			continue ;
		}
		d++;
	}
}
