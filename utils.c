/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:24:21 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/28 19:18:55 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exist(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (0);
	return (1);
}

int	check_command(t_creat *list)
{
	while (list && ft_strcmp(list-> token, "PIP"))
	{
		if (!ft_strcmp(list -> token, "CMD"))
			return (1);
		list = list -> next;
	}
	return (0);
}

void	ft_lstadd_back(t_creat **lst, t_creat *new)
{
	t_creat	*tmp;

	if (!lst)
		return ;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	tmp -> next = new;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i] || s1[i] < s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s1)
{
	int		a;
	int		res;
	char	*cpy;

	a = 0;
	if (!s1)
		return (0);
	res = ft_strlen(s1) + 1;
	cpy = (char *)malloc(res * sizeof(char));
	ft_malloc_protect(cpy);
	while (s1[a])
	{
		cpy[a] = s1[a];
		a++;
	}
	cpy[a] = '\0';
	return (cpy);
}
