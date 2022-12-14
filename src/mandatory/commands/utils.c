/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:16:04 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/13 21:19:59 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	try_to_execute(t_command command, t_commands commands)
{
	int	result;

	result = execve(command.argv[0], command.argv, command.envp);
	if (result < 0)
	{
		ft_error_message("command not found", command.name);
		free(command.name);
		ft_free_matrix(command.argv);
		free(commands.self);
		exit(127);
	}
}

pid_t	ft_throw_to_child(
	void (*f) (t_command command, t_commands commands),
	t_command command,
	t_commands commands,
	t_program_descriptors *descriptors,
	int is_last_command
)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_throw_error("Error during the creation of a new process");
	if (pid == 0)
	{
		if (command.index == 0 && descriptors->infile_fd != -1)
			dup2(descriptors->infile_fd, STDIN_FILENO);
		else
			dup2(descriptors->pip[READ], STDIN_FILENO);
		if (is_last_command)
			dup2(descriptors->outfile_fd, STDOUT_FILENO);
		else
			dup2(descriptors->pip[WRITE], STDOUT_FILENO);
		close(descriptors->pip[READ]);
		close(descriptors->pip[WRITE]);
		close(descriptors->outfile_fd);
		if (descriptors->infile_fd != -1)
			close(descriptors->infile_fd);
		f(command, commands);
		exit(0);
	}
	return (pid);
}
