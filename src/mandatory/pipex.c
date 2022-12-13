/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/12 21:27:21 by kmatos-s         ###   ########.fr       */
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

static void	wait_commands(t_command *commands, int n_commands)
{
	int	i;
	int	status;

	while (i < n_commands)
	{
		if (waitpid(commands[i].process, &status, 0) == -1)
			ft_exit_error("waitpid", 1);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			if (waitpid(commands[i].process, &status, 0) == -1)
				ft_exit_error("waitpid", 1);
			if (WIFEXITED(status) && i == n_commands - 1)
				exit(WIFEXITED(status));
		}
		i++;
	}
}

static char	*execute_commands(
	char **commands_str,
	t_enviroment program_env,
	t_program_descriptors *descriptors
)
{
	int			i;
	int			n_commands;
	t_command	*commands;
	char		*output;

	i = 0;
	output = NULL;
	n_commands = ft_mtxlen(commands_str);
	commands = get_commands_from(commands_str, program_env);
	if (pipe(descriptors->pip) == -1)
		ft_exit_error("Could not create pipe", 1);
	while (i < n_commands)
	{
		commands[i].process = execute_command(commands[i],
				descriptors, i == n_commands - 1);
		close(descriptors->pip[WRITE]);
		free(commands[i].name);
		ft_free_matrix(commands[i].argv);
		i++;
	}
	close(descriptors->pip[READ]);
	close(descriptors->pip[WRITE]);
	wait_commands(commands, n_commands);
	free(commands);
	return (output);
}

void	pipex(
	char *infile_name,
	char **commands,
	char *outfile_name,
	t_enviroment program_env
)
{
	t_program_descriptors	descriptors;

	if (access(infile_name, R_OK) == -1)
	{
		ft_error(infile_name);
		commands++;
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
	execute_commands(commands, program_env, &descriptors);
	if (descriptors.infile_fd != -1)
		close(descriptors.infile_fd);
	close(descriptors.outfile_fd);
}
