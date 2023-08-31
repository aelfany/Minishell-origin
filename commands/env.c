/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:00:50 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/28 17:21:09 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	ft_error_env(char **opt)
{
	if (opt[1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(opt[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exitstatus = 127;
		return (-1);
	}
	return (0);
}

void	ft_env(char **opt, t_env *envr)
{
	int		i;
	t_env	*ptr;

	i = 0;
	ptr = envr;
	if (!envr)
		return ;
	if (envr->name == NULL)
		return ;
	if (ft_error_env(opt) == -1)
		return ;
	while (ptr)
	{
		if (ptr->hidden_flag == 0 && ptr->name != NULL && ptr->value != NULL)
			printf("%s=%s\n", ptr->name, ptr->value);
		else if (ptr->hidden_flag == 0
			&& ptr->name != NULL && ptr->value == NULL
			&& ptr->uninitialized == 0)
			printf("%s=\n", ptr->name);
		ptr = ptr->next;
	}
}
