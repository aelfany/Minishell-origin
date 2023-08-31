/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:34:23 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/30 19:40:08 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_expand_cases(char *str, int x)
{
	if (str[x] == '$' && str[x + 1] == '*')
		return (1);
	return (0);
}

int	is_yes(char c)
{
	if (c == '|' || c == '<' || c == '>' || is_wts(c))
		return (1);
	return (0);
}

int	wc(char *str)
{
	int	x;
	int	count;

	x = 0;
	count = 0;
	if (!str)
		return (0);
	if (!is_wts(str[0]))
		count++;
	while (str[x])
	{
		if ((is_wts(str[x]) && !is_wts(str[x + 1])) && str[x + 1] != '\0')
			count++;
		x++;
	}
	return (count);
}

void	check_expand_new(char *str, int *x, t_creat **res, t_env *env)
{
	t_var	u;

	u.join = NULL;
	u.a = *x;
	while (str[u.a])
	{
		if (str[u.a] == '$')
			u.join = ft_strjoin_free(u.join, expand_word(str, &u.a, env), 1, 1);
		if (str[u.a] == '"' || str[u.a] == '\'')
			u.join = ft_strjoin_free(u.join, quts(str, &u.a, env), 1, 1);
		if (str[u.a] && str[u.a] != '$' && not(str[u.a]))
			u.join = _remallc(u.join, str[u.a]);
		if (wc(u.join) > 1)
			u.join = insert_expand_word(res, &u.join);
		if (!str[u.a] || is_yes(str[u.a]))
			break ;
		if (str[u.a] != '$')
			u.a++;
	}
	(*x) = u.a;
	if (u.join[0] != 0)
		insert(res, u.join, "CMD", 0);
	else
		free(u.join);
}
