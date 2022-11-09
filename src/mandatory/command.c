/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:11:40 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/08 22:05:28 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	parse_command_string(char *command, char *path)
{
	t_command	parsed_command;
	int			first_space_pos;
	char		**divided;

	divided = ft_split(command, ' ');
	parsed_command.name = divided[0];
	parsed_command.argv[0] = get_binary_path(path, parsed_command.name);
	parsed_command.argv = divided + 1; // TODO -> Create a function to push new items to matrix
	if (!parsed_command.argv[0])
		ft_throw_error("Command Not Found");
	return (parsed_command);
}
