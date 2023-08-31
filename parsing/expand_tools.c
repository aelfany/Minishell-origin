/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:43:03 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/28 15:43:33 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_expand_case(char c)
{
	if (c == '_' || c == '\0')
		return (0);
	if (!ft_isalpha(c) && !ft_isdigit(c))
		return (1);
	return (0);
}
