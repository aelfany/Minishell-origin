/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:41:40 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/28 22:27:29 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_error_rd(t_creat *res, int n)
{
	if (n == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(res->cmd);
	}
	return (-1);
}

static	int	rd_in(t_creat **ptr, t_vars **var)
{
	if ((*var)->in != -1)
	{
		close ((*var)->in);
		(*var)->in = open((*ptr)->cmd, O_RDONLY);
	}
	else
		(*var)->in = open((*ptr)->cmd, O_RDONLY);
	if ((*var)->in == -1)
		(*var)->failed_rd = ft_error_rd(*ptr, 0);
	else
		dup2((*var)->in, 0);
	if ((*var)->failed_rd == -1)
		g_exitstatus = 1;
	else
		g_exitstatus = 0;
	return (0);
}

static	int	rd_out(t_creat **ptr, t_vars **var)
{
	if ((*var)->out != -1)
	{
		close((*var)->out);
		(*var)->out = open((*ptr)->cmd, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else
		(*var)->out = open((*ptr)->cmd, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if ((*var)->out == -1)
		(*var)->failed_rd = ft_error_rd(*ptr, 0);
	else
		dup2((*var)->out, 1);
	if ((*var)->failed_rd == -1)
		g_exitstatus = 1;
	else
		g_exitstatus = 0;
	return (0);
}

static	int	rd_ap(t_creat **ptr, t_vars **var)
{
	if ((*var)->out != -1)
	{
		close((*var)->out);
		(*var)->out = open((*ptr)->cmd, O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	else
		(*var)->out = open((*ptr)->cmd, O_RDWR | O_CREAT | O_APPEND, 0644);
	if ((*var)->out == -1)
		(*var)->failed_rd = ft_error_rd(*ptr, 0);
	else
		dup2((*var)->out, 1);
	if ((*var)->failed_rd == -1)
		g_exitstatus = 1;
	else
		g_exitstatus = 0;
	return (0);
}

void	ft_open_redirections(t_creat **res, t_vars **var)
{
	t_creat	*ptr;
	t_vars	*ptr_var;
	int		flag;

	ptr = *res;
	ptr_var = *var;
	flag = ft_check_last(*res);
	ptr = *res;
	while (ptr && ptr_var->failed_rd != -1 && flag != 2)
	{
		if (ft_strcmp(ptr->token, "RDIN") == 0 && flag != 1)
			rd_in(&ptr, &ptr_var);
		if (ft_strcmp(ptr->token, "RDOUT") == 0)
			rd_out(&ptr, &ptr_var);
		if (ft_strcmp(ptr->token, "RD_AP") == 0)
			rd_ap(&ptr, &ptr_var);
		ptr = ptr->next;
	}
}
