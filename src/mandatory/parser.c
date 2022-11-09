/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:35:39 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/08 19:42:59 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_var_from_env(char *name, char **envp)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], name, name_len))
			if (envp[i][name_len] == '=')
				return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}

char	*join_paths(char *path1, char *path2)
{
	char	*result;
	char	*temporary;

	temporary = ft_strjoin(path1, "/");
	result = ft_strjoin(temporary, path2);
	free(temporary);
	return (result);
}

char	*get_binary_path(char *path, char *bin_name)
{
	char	**bin_folder_paths;
	char	*binary;
	int		i;

	i = 0;
	bin_folder_paths = ft_split(path, ':');
	while (bin_folder_paths[i])
	{
		binary = join_paths(bin_folder_paths[i], bin_name);
		if (access(binary, X_OK) == 0)
		{
			ft_free_matrix(bin_folder_paths);
			return (binary);
		}
		free(binary);
		i++;
	}
	ft_free_matrix(bin_folder_paths);
	return (NULL);
}
