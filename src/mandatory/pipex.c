/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/12 22:18:11 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	try_to_execute(t_command command)
{
	int	result;

	result = execve(command.argv[0], command.argv, command.envp);
	if (result < 0)
	{
		ft_error_message("command not found", command.name);
		exit(127);
	}
}

static pid_t	execute_command(
	t_command command,
	t_program_descriptors *descriptors,
	int is_last_command
)
{
	pid_t	process;

	process = ft_throw_to_child(
			&try_to_execute,
			command,
			descriptors,
			is_last_command
			);
	return (process);
}

static void	wait_commands(t_commands commands)
{
	unsigned int	i;
	int				status;

	while (i < commands.length)
	{
		if (waitpid(commands.self[i].process, &status, 0) == -1)
			ft_exit_error("waitpid", 1);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			if (waitpid(commands.self[i].process, &status, 0) == -1)
				ft_exit_error("waitpid", 1);
			if (WIFEXITED(status) && i == commands.length - 1)
				exit(WIFEXITED(status));
		}
		i++;
	}
}

static char	*execute_commands(
	t_commands commands,
	t_program_descriptors *descriptors
)
{
	unsigned int	i;
	char			*output;

	i = 0;
	output = NULL;
	if (pipe(descriptors->pip) == -1)
		ft_exit_error("Could not create pipe", 1);
	while (i < commands.length)
	{
		commands.self[i].process = execute_command(commands.self[i],
				descriptors, i == commands.length - 1);
		close(descriptors->pip[WRITE]);
		free(commands.self[i].name);
		ft_free_matrix(commands.self[i].argv);
		i++;
	}
	close(descriptors->pip[READ]);
	close(descriptors->pip[WRITE]);
	wait_commands(commands);
	free(commands.self);
	return (output);
}

void	pipex(
	char *infile_name,
	char **commands_strs,
	char *outfile_name,
	t_enviroment program_env
)
{
	t_program_descriptors	descriptors;
	t_commands				commands;

	if (access(infile_name, R_OK) == -1)
	{
		ft_error(infile_name);
		commands_strs++;
		descriptors.infile_fd = -1;
	}
	else
	{
		descriptors.infile_fd = open(infile_name, O_RDONLY);
		if (descriptors.infile_fd == -1)
			ft_exit_error(infile_name, 1);
	}
	descriptors.outfile_fd = open(
			outfile_name,
			O_CREAT | O_WRONLY | O_TRUNC,
			0664
			);
	if (descriptors.outfile_fd == -1)
		ft_exit_error(outfile_name, 1);
	commands = get_commands_from(commands_strs, program_env);
	execute_commands(commands, &descriptors);
	if (descriptors.infile_fd != -1)
		close(descriptors.infile_fd);
	close(descriptors.outfile_fd);
}
