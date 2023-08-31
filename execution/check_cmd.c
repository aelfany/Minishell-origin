/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 00:32:26 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/23 13:11:18 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// to check for required built ins

int	check_built_ins(t_creat *res)
{
	if (ft_strcmp(res->cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(res->cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(res->cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(res->cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(res->cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(res->cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(res->cmd, "exit") == 0)
		return (1);
	return (0);
}
