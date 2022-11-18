/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:11:40 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/17 21:51:06 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	parse_command_string(char *command, char *path)
{
	t_command	parsed_command;
	char		**divided;
	int			i;

	i = 1;
	divided = ft_split(command, ' ');
	parsed_command.name = divided[0];
	parsed_command.argv = NULL;
	parsed_command.argv = ft_mtxpush(parsed_command.argv, get_binary_path(path, parsed_command.name));
	while (divided[i])
	{
		parsed_command.argv = ft_mtxpush(parsed_command.argv, divided[i]);
		i++;
	}
	if (!parsed_command.argv[0])
		ft_throw_error("Command Not Found");
	return (parsed_command);
}
