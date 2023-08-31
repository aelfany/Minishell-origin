/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:55:44 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/28 21:04:26 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_last(char *str, int *flag, char c)
{
	int	f;
	int	a;

	a = 1;
	f = 0;
	while (str[a])
	{
		if (str[a] == c)
		{
			f = 1;
			break ;
		}
		a++;
	}
	(*flag) = f;
	return (a);
}

int	not(char c)
{
	if (c == '\'' || c == '"' || c == '|' || c == '<' 
		|| c == '>' || c == '$' || is_wts(c))
		return (0);
	return (1);
}

int	counter(char *str, char c)
{
	int	a;
	int	count;

	a = 0;
	count = 0;
	while (str[++a])
		if (str[a] == c)
			count++;
	return (count);
}

void	error_handler(char *str)
{
	if (!ft_strcmp(str, "RD") || !ft_strcmp(str, "HRD") || 
		!ft_strcmp(str, "RDP"))
	{
		ft_putstr_fd("minishell: syntax error near", 2);
		ft_putstr_fd(" unexpected token `newline'\n", 2);
		g_exitstatus = 258;
	}
	else if (!ft_strcmp(str, "QT"))
		ft_putstr_fd("minishell: syntax error near unexpected token `QT'\n", 2);
	else if (!ft_strcmp(str, "PIP"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_exitstatus = 258;
	}
	else
	{
		ft_putstr_fd("minishell: ", 2); 
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2); 
		g_exitstatus = 1;
	}
}
