/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:19:37 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/31 18:40:00 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*insert_expand_word(t_creat **res, char **word)
{
	char	**spl;
	char	*join;
	int		b;

	b = 0;
	join = NULL;
	spl = split_word(*word, "\t ");
	join = ft_strjoin_free(join, spl[b++], 1, 1);
	insert(res, join, "CMD", 0);
	while (spl[b + 1])
		insert(res, spl[b++], "CMD", 0);
	free((*word));
	(*word) = spl[b];
	free(spl); 
	return ((*word));
}

char	*expand_hrd(t_env *env, int count, char *word)
{
	int	a;

	a = -1;
	while (env)
	{
		if (!ft_strcmp(env -> name, word))
		{
			if (count % 2)
			{
				free(word);
				word = NULL;
				while (env->value && env -> value[++a])
					word = _remallc(word, env -> value[a]);
			}
			return (word);
		}
		env = env -> next;
	}
	if (env == NULL && count % 2)
		word[0] = 0;
	return (word);
}

char	*split_expand(char *str)
{
	char	*word;
	char	**spl;

	word = NULL;
	if (wc(str) == 1)
	{
		spl = split_word(str, "\t ");
		word = spl[0];
		free(spl);
	}
	return (word);
}

char	*expand(t_env *env, int count, char *word)
{
	int	a;

	a = -1;
	while (env)
	{
		if (!ft_strcmp(env -> name, word))
		{
			if (count % 2)
			{
				free(word);
				word = split_expand(env -> value);
				if (word == NULL)
					while (env->value && env -> value[++a])
						word = _remallc(word, env -> value[a]);
			}
			return (word);
		}
		env = env -> next;
	}
	if (env == NULL && count % 2)
		word[0] = 0;
	return (word);
}

char	*expand_red(t_env *env, int count, char *word, t_creat **res)
{
	t_var	u;

	u.a = -1;
	u.mark = 0;
	while (env)
	{
		if (wc(env -> value) == 1 &&!ft_strcmp(env -> name, word))
		{
			u.mark = 1;
			if (count % 2)
			{
				free(word);
				word = NULL;
				while (env -> value[++u.a])
					word = _remallc(word, env -> value[u.a]);
			}
			return (word);
		}
		env = env -> next;
	}
	if (u.mark == 0)
		insert(res, ft_strdup(word), word, 1);
	if (env == NULL && count % 2)
		word[0] = 0;
	return (word);
}
