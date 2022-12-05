/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/05 20:38:23 by kmatos-s         ###   ########.fr       */
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

static char	*execute_command(char *command_str, t_enviroment program_env)
{
	char		*output;
	int			stdout_fd;
	t_command	command;

	output = NULL;
	command = parse_command_string(command_str, program_env);
	if (!command.argv[0][0])
		ft_error_message("command not found", command.name);
	else
	{
		stdout_fd = std__switch_out_scope(1);
		ft_throw_to_child(&try_to_execute, command);
		if (command.argv[0])
			output = ft_read_file_fd(stdout_fd);
		std__switch_out_scope(0);
	}
	free(command.name);
	ft_free_matrix(command.argv);
	return (output);
}

static char	*execute_commands(char **commands, t_enviroment program_env)
{
	int		i;
	char	*output;

	i = 0;
	output = NULL;
	while (commands[i])
	{
		free(output);
		output = execute_command(commands[i], program_env);
		if (commands[i + 1])
			std__write_in(output);
		i++;
	}
	return (output);
}

void	pipex(char *infile_name, char **commands, char *outfile_name, t_enviroment program_env)
{
	char	*infile;
	int		outfile_fd;
	char	*output;

	if (access(infile_name, R_OK) == -1)
	{
		ft_error(infile_name);
		commands++;
	}
	infile = ft_read_file(infile_name);
		std__write_in(infile);
	free(infile);
	output = execute_commands(commands, program_env);
	outfile_fd = open(outfile_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (outfile_fd == -1)
	{
		free(output);
		ft_exit_error(outfile_name, 1);
	}
	ft_fprintf(outfile_fd, output);
	close(outfile_fd);
	free(output);
}
