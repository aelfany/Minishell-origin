/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:24:10 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/24 13:30:25 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_hrd(char *token)
{
	if (ft_strcmp(token, "HRD") == 0)
		return (0);
	if (ft_strcmp(token, "HRD_SQ") == 0)
		return (0);
	if (ft_strcmp(token, "HRD_DQ") == 0)
		return (0);
	return (-1);
}

int	ft_exp_check(char *token)
{
	if (ft_strcmp(token, "HRD") == 0)
		return (0);
	return (-1);
}
