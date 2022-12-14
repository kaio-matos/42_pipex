/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/13 21:24:05 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_program_descriptors	handle_files_creation(
									char *infile_name,
									char *outfile_name
									);

void	pipex(
	char *infile_name,
	char **commands_strs,
	char *outfile_name,
	t_enviroment program_env
)
{
	t_program_descriptors	descriptors;
	t_commands				commands;

	descriptors = handle_files_creation(infile_name, outfile_name);
	if (descriptors.infile_fd == -1)
		commands_strs++;
	commands = parse_commands(commands_strs, program_env);
	execute_commands(commands, &descriptors);
	if (descriptors.infile_fd != -1)
		close(descriptors.infile_fd);
	close(descriptors.outfile_fd);
}

static t_program_descriptors	handle_files_creation(
	char *infile_name,
	char *outfile_name
)
{
	t_program_descriptors	descriptors;

	if (access(infile_name, R_OK) == -1)
	{
		ft_error(infile_name);
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
	return (descriptors);
}
