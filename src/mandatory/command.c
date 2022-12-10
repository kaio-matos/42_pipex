/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:11:40 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/09 21:02:04 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	*reset_command(t_command *command)
{
	command->argv = NULL;
	command->envp = NULL;
	command->index = -1;
	command->name = NULL;
	command->process = -1;

	return (command);
}

t_command	parse_command_string(char *command, t_enviroment program_env)
{
	t_command	parsed_command;
	char		**divided;
	char		*path;
	int			i;

	i = 1;
	reset_command(&parsed_command);
	divided = ft_spliti(command, ' ');
	if (!divided)
		return (parsed_command);
	parsed_command.name = divided[0];
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

t_command	*get_commands_from(char **commands_str, t_enviroment program_env)
{
	int			i;
	t_command	command;
	t_command	*commands;
	int			n_commands;

	i = 0; 
	n_commands = ft_mtxlen(commands_str);
	commands = malloc(sizeof(t_command) * n_commands);
	while (i < n_commands && commands_str[i])
	{
		command = parse_command_string(commands_str[i], program_env);
		if (command.argv[0])
			commands[i] = command;
		commands[i].index = i;
		i++;
	}
	return (commands);
}
