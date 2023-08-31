/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:19:37 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/31 14:03:06 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free2(t_creat *res)
{
	free(res -> cmd);
	free(res -> token);
	free(res);
}

int	skip_space(char *str)
{
	int	a;

	a = 0;
	while (str[a] == '\t' || str[a] == '\n' || str[a] == '\v'
		|| str[a] == '\f' || str[a] == '\r' || str[a] == ' ')
		a++;
	return (a);
}

int	add_red_token(t_creat **res, char *word, char c, int x)
{
	if (c == '<')
		insert(res, word, "RDIN", 0);
	else if (c == '>')
		insert(res, word, "RDOUT", 0);
	return (x);
}

int	check_rederction(char *str, t_creat **res, char c, t_env *env)
{
	t_str	u;

	u.word = NULL;
	u.b = 1;
	u.mark = 0;
	u.b += skip_space(str + u.b);
	if (str[u.b] == '"' || str[u.b] == '\'')
		u.flag = '"'; 
	while (str[u.b] && !is_wts(str[u.b]) && exist(str[u.b]))
	{
		if (str[u.b] == '$')
			u.word = ft_strjoin_free(u.word, \
				expand_word_red(str, &u.b, env, res), 1, 1);
		while (exist(str[u.b]) && str[u.b] && (str[u.b] != '"'
				&& str[u.b] != '\'') && !is_wts(str[u.b]) && str[u.b] != '$')
			u.word = _remallc(u.word, str[u.b++]);
		if (str[u.b] && !is_wts(str[u.b]) && exist(str[u.b]) && str[u.b] != '$')
			u.word = ft_strjoin_free(u.word, quts(str, &u.b, env), 1, 1);
		if (str[u.b] && !is_wts(str[u.b]) && exist(str[u.b]) && str[u.b] != '$')
			u.b++;
	}
	if (!u.word && u.flag != '"' && u.flag != '\'')
		return (insert(res, u.word, "RD", 1), u.b);
	return (add_red_token(res, u.word, c, u.b), u.b);
}

void	rederction_apn(char *str, int *x, t_creat **res, t_env *env)
{
	t_str	u;

	u.word = NULL;
	u.b = x[0] + 2;
	u.b += skip_space(str + u.b);
	if (str[u.b] == '"' || str[u.b] == '\'')
		u.flag = '"'; 
	while (str[u.b] && !is_wts(str[u.b]) && exist(str[u.b]))
	{
		if (str[u.b] == '$')
			u.word = ft_strjoin_free(u.word, \
				expand_word_red(str, &u.b, env, res), 1, 1);
		while (exist(str[u.b]) && str[u.b] && (str[u.b] != '"'
				&& str[u.b] != '\'') && !is_wts(str[u.b]) && str[u.b] != '$')
			u.word = _remallc(u.word, str[u.b++]);
		if (str[u.b] && !is_wts(str[u.b]) && exist(str[u.b]) && str[u.b] != '$')
			u.word = ft_strjoin_free(u.word, quts(str, &u.b, env), 1, 1);
		if (str[u.b] && !is_wts(str[u.b]) && exist(str[u.b]) && str[u.b] != '$')
			u.b++;
	}
	(*x) = u.b;
	if (!u.word && u.flag != '"' && u.flag != '\'')
		insert(res, u.word, "RD", 1);
	insert(res, u.word, "RD_AP", 0);
}
