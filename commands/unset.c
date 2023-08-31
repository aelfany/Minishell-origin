/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:03:04 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/26 18:25:08 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_remove_first(t_env **envr, t_env **ptr, t_env **prev)
{
	if ((*envr)->next != NULL)
		*envr = (*envr)->next;
	if ((*ptr)->name != NULL)
		free((*ptr)->name);
	if ((*ptr)->value != NULL)
		free((*ptr)->value);
	(*prev) = (*ptr);
	(*ptr) = (*ptr)->next;
	free((*prev));
}

static void	ft_remove_others(t_env **ptr, t_env **prev)
{
	(*prev)->next = (*prev)->next->next;
	(*ptr)->next = NULL;
	if ((*ptr)->name != NULL)
		free((*ptr)->name);
	if ((*ptr)->value != NULL)
		free((*ptr)->value);
	free((*ptr));
}

void	ft_unset_env(t_env **envr, t_env **ptr, t_env **prev, char *opt)
{
	int	i;

	i = 1;
	while ((*ptr))
	{
		if (ft_strcmp(opt, (*ptr)->name) == 0)
		{
			if (i == 1)
			{
				ft_remove_first(envr, ptr, prev);
				return ;
			}
			while (i > 2)
			{
				(*prev) = (*prev)->next;
				i--;
			}
			ft_remove_others(ptr, prev);
			break ;
		}
		(*ptr) = (*ptr)->next;
		i++;
	}
}

void	unset(t_env **envr, t_creat *res, int d)
{
	t_env	*ptr;
	t_env	*prev;

	ptr = *envr;
	prev = *envr;
	while (res->opt[d])
	{
		if (ft_export_parser(res->opt[d], 1) == -1)
		{
			d++;
			continue ;
		}
		ft_unset_env(envr, &ptr, &prev, res->opt[d]);
		ptr = *envr;
		prev = *envr;
		d++;
	}
}
