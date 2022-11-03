/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:35:39 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/03 20:58:03 by kmatos-s         ###   ########.fr       */
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

char	**generate_possible_bin_paths(char *path, char *bin_name)
{
	char	**bin_folder_paths;
	char	**possible_bin_paths;
	int		i;

	i = 0;
	bin_folder_paths = ft_split(path, ':');
	possible_bin_paths = ft_salloc((ft_chrcnt(path, ':') + 1) * sizeof(char *));
	while (bin_folder_paths[i])
	{
		possible_bin_paths[i] = join_paths(bin_folder_paths[i], bin_name);
		i++;
	}
	possible_bin_paths[i] = NULL;
	ft_free_matrix(bin_folder_paths);
	return (possible_bin_paths);
}
