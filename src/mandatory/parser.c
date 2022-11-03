/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:35:39 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/03 19:59:22 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_var_from_env(char *name, char	**envp)
{
	int i;
	int	name_len;

	i = 0;
	name_len =  ft_strlen(name);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], name, name_len))
			if (envp[i][name_len] == '=')
				return (envp[i]);
		i++;
	}
	return (name);
}
