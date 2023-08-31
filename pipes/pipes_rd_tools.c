/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_rd_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:52:49 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/26 15:22:28 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//checks which one is last either redirection or heredoc
// 0 for RDIN / RDOUT
// 1 FOR HRD
// -1 FOR NONE

int	rd_in_p(t_creat **ptr)
{
	int	fd;

	fd = open((*ptr)->cmd, O_RDONLY);
	if (fd == -1)
		fd = ft_error_rd_p(*ptr, 0);
	return (fd);
}

int	rd_out_p(t_creat **ptr)
{
	int	fd;

	fd = open((*ptr)->cmd, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		fd = ft_error_rd_p(*ptr, 0);
	return (fd);
}

int	rd_ap_p(t_creat **ptr)
{
	int	fd;

	fd = open((*ptr)->cmd, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		fd = ft_error_rd_p(*ptr, 0);
	return (fd);
}

int	ft_error_rd_p(t_creat *res, int n)
{
	if (n == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(res->cmd);
	}
	return (-1);
}
