/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:11:40 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/12 22:15:36 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void			fill_mtx(char ***mtx1, char **mtx2, int start);
static t_command	*reset_command(t_command *command);
static t_command	parse_command_string(char *command, t_enviroment program_env);

t_commands	get_commands_from(char **commands_str, t_enviroment program_env)
{
	unsigned int	i;
	t_command		command;
	t_commands		commands;

	i = 0;
	commands.length = ft_mtxlen(commands_str);
	commands.self = malloc(sizeof(t_command) * commands.length);
	while (i < commands.length && commands_str[i])
	{
		command = parse_command_string(commands_str[i], program_env);
		if (command.argv[0])
			commands.self[i] = command;
		commands.self[i].index = i;
		i++;
	}
	return (commands);
}

static void	fill_mtx(char ***mtx1, char **mtx2, int start)
{
	int	i;

	i = start;
	while (mtx2[i])
	{
		*mtx1 = ft_mtxpush(*mtx1, mtx2[i]);
		i++;
	}
}

static t_command	*reset_command(t_command *command)
{
	command->argv = NULL;
	command->envp = NULL;
	command->index = -1;
	command->name = NULL;
	command->process = -1;
	return (command);
}

static t_command	parse_command_string(char *command, t_enviroment program_env)
{
	t_command	cmd;
	char		**divided;
	char		*path;

	reset_command(&cmd);
	divided = ft_spliti(command, ' ');
	if (!divided)
		return (cmd);
	cmd.name = divided[0];
	cmd.envp = program_env.envp;
	path = get_var_from_env("PATH", program_env.envp);
	if (!path)
		ft_exit_error("Enviroment variable 'PATH' not found", 1);
	if (access(cmd.name, X_OK) == -1)
		cmd.argv = ft_mtxpush(cmd.argv, get_binary_path(path, cmd.name));
	else
		cmd.argv = ft_mtxpush(cmd.argv, ft_strdup(cmd.name));
	fill_mtx(&cmd.argv, divided, 1);
	free(divided);
	return (cmd);
}
