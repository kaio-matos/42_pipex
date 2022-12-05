/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:11:40 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/05 20:33:12 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	parse_command_string(char *command, t_enviroment program_env)
{
	t_command	parsed_command;
	char		**divided;
	char		*path;
	int			i;

	i = 1;
	divided = ft_spliti(command, ' ');
	parsed_command.name = divided[0];
	parsed_command.argv = NULL;
	parsed_command.envp = program_env.envp;
	path = get_var_from_env("PATH", program_env.envp);
	if (!path)
		ft_exit_error("Enviroment variable 'PATH' not found", 1);
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
