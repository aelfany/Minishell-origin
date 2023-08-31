/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:55:04 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/30 23:30:26 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_loop(char **opt)
{
	int	i;

	i = 0;
	if (opt == NULL)
		return ;
	while (opt[i])
	{
		free(opt[i]);
		i++;
	}
	free(opt);
}

void	free_opt(char **str)
{
	int	a;

	a = 1;
	if (str == NULL)
		return ;
	while (str[a])
	{
		free(str[a]);
		a++;
	}
	free(str);
}

void	free_res(t_creat *res)
{
	if (res == NULL)
		return ;
	if (res->cmd != NULL)
		free(res -> cmd);
	if (res->token != NULL)
		free(res->token);
	free_opt(res->opt);
	free(res);
}

void	free_list(t_creat **ptr)
{
	t_creat	*tmp;

	if (ptr == NULL)
		return ;
	tmp = *ptr;
	while (*ptr)
	{
		tmp = (*ptr);
		*ptr = (*ptr)->next;
		free_res(tmp);
	}
}

int	free_line(char *str)
{
	if (str[0] == '\0')
	{
		free(str);
		return (1);
	}
	return (0);
}
