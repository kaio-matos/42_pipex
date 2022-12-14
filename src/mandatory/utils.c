/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:30:47 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/13 20:58:49 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *message)
{
	perror(message);
}

void	ft_exit_error(char *message, int number)
{
	perror(message);
	exit(number);
}

void	ft_error_message(char *message, char *argument)
{
	ft_fprintf(2, "%s: %s\n", message, argument);
}

int	ft_chrcnt(char *string, char c)
{
	int	counter;

	counter = 0;
	while (*string)
	{
		if (*string == c)
			counter++;
		string++;
	}
	return (counter);
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
