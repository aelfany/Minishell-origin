/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:17:26 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/26 15:21:53 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_id_fillup(char *str)
{
	int		i;
	int		d;
	char	*str_id;

	i = 0;
	d = 0;
	str_id = malloc(1 * ft_strlen_delim(str, '=') + 1);
	ft_malloc_protect(str_id);
	while (str[i] != '=' && str[i])
	{
		if (str[i] == '+')
		{
			i++;
			continue ;
		}
		str_id[d] = str[i];
		d++;
		i++;
	}
	str_id[d] = '\0';
	return (str_id);
}

int	ft_export_last(t_env **envr, char **opt, int d)
{
	t_env	*ptr;
	int		i;

	ptr = (*envr);
	i = 0;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = malloc(sizeof(t_env) * 1);
	ptr = ptr->next;
	i = calc_size(opt[d], '=');
	if (opt[d][i] == '\0')
	{
		ptr->name = malloc(1 * (i + 1));
		ft_fillup(ptr, opt[d]);
		ptr->uninitialized = 1;
		g_exitstatus = 0;
		return (1);
	}
	ptr->name = malloc(1 * (i + 1));
	ft_fillup(ptr, opt[d]);
	ptr->value = malloc(1 * (ft_strlen(opt[d]) - 1) + 1);
	ft_fillup_envr(ptr, opt[d]);
	ptr = *envr;
	g_exitstatus = 0;
	return (0);
}

void	print_env(t_env *envr)
{
	t_env	*ptr;

	ptr = envr;
	while (ptr)
	{
		if (ptr->uninitialized == 1 && ptr->value == NULL)
			printf("declare -x %s\n", ptr->name);
		if (ptr->value == NULL && ptr->uninitialized == 0)
			printf("declare -x %s=" "\n", ptr->name);
		else if (ptr->hidden_flag == 0 
			&& ptr->name != NULL && ptr->value != NULL)
			printf("declare -x %s=\"%s\"\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
}
