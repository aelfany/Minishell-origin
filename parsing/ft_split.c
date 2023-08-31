/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:52:27 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/27 13:49:41 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*ft_chr(const char *str, int c)
{
	int	a;

	a = 0;
	while (str[a])
	{
		if (str[a] != c && str[a])
			return ((char *)&str[a]);
		a++;
	}
	return (0);
}

static	int	countlen(const char *str, char c)
{
	int	x;

	x = 0;
	str = ft_chr(str, c);
	while (str[x] != c && str[x])
		x++;
	return (x + 1);
}

static	char	**ft_creat(const char *s, int size, char c)
{
	int		x;
	int		l;
	char	**tab;

	l = 0;
	x = 0;
	tab = malloc((size + 1) * sizeof(char *));
	if (!tab)
		return (0);
	while (x < size)
	{
		s = ft_chr((&s[l]), c);
		l = countlen(s, c);
		tab[x] = malloc(countlen(s, c) * sizeof(char));
		if (!tab[x])
		{
			while (x-- >= 0)
				free(tab[x]);
			free(tab);
		}
		x++;
	}
	return (tab);
}

static	char	**tab1(char const *s, int size, char c)
{
	char	**tab;
	int		a;
	int		y;
	int		l;

	a = 0;
	l = 0;
	tab = ft_creat(s, size, c);
	if (!tab)
		return (0);
	while (a < size)
	{
		y = 0;
		s = ft_chr((&s[l]), c);
		l = countlen(s, c);
		while (y < l - 1)
		{
			tab[a][y] = s[y];
			y++;
		}
		tab[a][y] = '\0';
		a++;
	}
	tab[size] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		x;
	int		count;

	x = 0;
	count = 0;
	if (!s)
		return (0);
	if (s[0] != c && s[0] != '\0')
		count++;
	while (s[x])
	{
		if (s[x] == c && s[x + 1] != c && s[x + 1] != '\0')
			count++;
		x++;
	}
	tab = tab1(s, count, c);
	return (tab);
}
