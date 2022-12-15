/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:13:13 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/14 21:08:21 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		wait_commands(
					t_commands commands,
					t_program_descriptors descriptors
					);
static pid_t	execute_command(
					t_command command,
					t_commands commands,
					t_program_descriptors *descriptors,
					int is_last_command
					);

void	execute_commands(
	t_commands commands,
	t_program_descriptors *descriptors
)
{
	unsigned int	i;

	i = 0;
	if (pipe(descriptors->pip) == -1)
		ft_exit_perror("Could not create pipe", EXIT_FAILURE);
	while (i < commands.length)
	{
		commands.self[i].process = execute_command(
				commands.self[i],
				commands,
				descriptors,
				i == commands.length - 1
				);
		i++;
	}
	close(descriptors->pip[READ]);
	close(descriptors->pip[WRITE]);
	wait_commands(commands, *descriptors);
}

static pid_t	execute_command(
	t_command command,
	t_commands commands,
	t_program_descriptors *descriptors,
	int is_last_command
)
{
	pid_t	process;

	process = ft_throw_to_child(
			&try_to_execute,
			command,
			commands,
			descriptors,
			is_last_command
			);
	return (process);
}

static void	wait_commands(
	t_commands commands,
	t_program_descriptors descriptors
)
{
	unsigned int	i;
	int				status;

	i = 0;
	while (i < commands.length)
	{
		if (waitpid(commands.self[i].process, &status, 0) == -1)
		{
			free_commands(&commands);
			if (descriptors.infile_fd != -1)
				close(descriptors.infile_fd);
			close(descriptors.outfile_fd);
			ft_exit_perror("waitpid", EXIT_FAILURE);
		}
		if (i == commands.length - 1 && WIFEXITED(status))
		{
			free_commands(&commands);
			if (descriptors.infile_fd != -1)
				close(descriptors.infile_fd);
			close(descriptors.outfile_fd);
			exit(WEXITSTATUS(status));
		}
		i++;
	}
}
