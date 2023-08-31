/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:07:09 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/28 19:36:36 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	add_back_token(t_creat **res, char *word, char flag, int x)
{
	if (flag == '\'')
		insert(res, word, "HRD_SQ", 0);
	else if (flag == '"')
		insert(res, word, "HRD_DQ", 0);
	else
		insert(res, word, "HRD", 0);
	return (x);
}

char	*qt_herdoc(char *str, int *x)
{
	int		b;
	char	flag;
	char	*word;

	flag = '\'';
	b = x[0];
	if (str[b] == '"')
		flag = '"';
	word = malloc(2);
	ft_malloc_protect(word);
	word[0] = 0;
	b++;
	while (str[b] != flag && str[b])
	{
		word = _remallc(word, str[b]);
		if (!str[b])
			break ;
		if (str[b])
			b++;
	}
	(*x) = b;
	return (word);
}

int	check_heredoc_case(char *str, int b, int count)
{
	if (str[b] == '$' && (str[b + 1] == '"' \
	|| str[b + 1] == '\'') && count % 2)
		return (1);
	return (0);
}

void	check_heredoc(char *str, int *x, t_creat **res)
{
	t_var	u;

	u.word = NULL;
	u.b = x[0] + 2;
	while (is_wts(str[u.b]))
		u.b++;
	u.count = u.b;
	while (str[u.count] == '$')
		u.count++;
	u.count -= u.b;
	while (str[u.b] && !is_wts(str[u.b]) && exist(str[u.b]))
	{
		u.b += check_heredoc_case(str, u.b, u.count);
		if ((str[u.b] != '"' && str[u.b] != '\''))
			u.word = _remallc(u.word, str[u.b]);
		if ((str[u.b] == '"' || str[u.b] == '\''))
		{
			u.flag = str[u.b];
			u.word = ft_strjoin_free(u.word, qt_herdoc(str, &u.b), 1, 1);
		}
		u.b++;
	}
	if (!u.word && u.flag != '"' && u.flag != '\'')
		insert(res, u.word, "RD", 1);
	(*x) = add_back_token(res, u.word, u.flag, u.b);
}
