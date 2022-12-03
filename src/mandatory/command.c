/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:11:40 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/02 21:55:20 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	parse_command_string(char *command, char *path)
{
	t_command	parsed_command;
	char		**divided;
	int			i;

	i = 1;
	divided = ft_spliti(command, ' ');
	parsed_command.name = divided[0];
	parsed_command.argv = NULL;
	if (access(parsed_command.name, X_OK) == -1)
		parsed_command.argv = ft_mtxpush(parsed_command.argv, get_binary_path(path, parsed_command.name));
	else
		parsed_command.argv = ft_mtxpush(parsed_command.argv, ft_strdup(parsed_command.name));
	while (divided[i])
	{
		parsed_command.argv = ft_mtxpush(parsed_command.argv, divided[i]);
		i++;
	}
	free(divided);
	return (parsed_command);
}
