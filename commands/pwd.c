/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:03:37 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/16 13:21:07 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	pwd(t_env *envr)
{
	t_env	*ptr;

	ptr = envr;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "1PWD") == 0)
		{
			printf("%s\n", ptr->value);
			break ;
		}
		ptr = ptr->next;
	}
	return (0);
}
