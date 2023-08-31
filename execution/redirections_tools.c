/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:59:19 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/24 21:59:42 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//checks which one is last either redirection or heredoc
// 0 for RDIN / RDOUT
// 1 FOR HRD
// -1 FOR NONE

int	ft_check_last(t_creat *res)
{
	t_creat	*ptr;
	int		i;

	ptr = res;
	i = 2;
	while (ptr)
	{
		if (ft_strcmp(ptr->token, "RDIN") == 0)
			i = 0;
		else if (ft_strcmp(ptr->token, "RDOUT") == 0)
			i = 0;
		else if (ft_strcmp(ptr->token, "RD_AP") == 0)
			i = 0;
		else if (ft_strcmp(ptr->token, "HRD_DQ") == 0)
			i = 1;
		else if (ft_strcmp(ptr->token, "HRD_SQ") == 0)
			i = 1;
		else if (ft_strcmp(ptr->token, "HRD") == 0)
			i = 1;
		ptr = ptr->next;
	}
	if (i == 2)
		return (-1);
	return (i);
}
