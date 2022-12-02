/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/01 21:58:34 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	try_to_execute(void)
{
	int	result;

	result = execve(g__enviroment()->command.argv[0], g__enviroment()->command.argv, g__enviroment()->envp);
	if (result < 0)
	{
		ft_error_message("command not found", g__enviroment()->command.name);
		exit(127);
	}
}


char	*execute_command(char *command, char *path)
{
	char	*output;
	int		stdout_fd;

	g__enviroment()->command = parse_command_string(command, path);
	if (!g__enviroment()->command.argv[0][0])
	{
		ft_error_message("command not found", g__enviroment()->command.name);
		free(g__enviroment()->command.name);
		ft_free_matrix(g__enviroment()->command.argv);
		exit(127);
	}
	stdout_fd = std__switch_out_scope(1);
	ft_throw_to_child(&try_to_execute);
	if (g__enviroment()->command.argv[0])
		output = ft_read_file_fd(stdout_fd);
	free(g__enviroment()->command.name);
	ft_free_matrix(g__enviroment()->command.argv);
	std__switch_out_scope(0);
	return (output);
}

char	*execute_commands(char **commands, char *path)
{
	int		i;
	char	*output;

	i = 0;
	output = NULL;
	while (commands[i])
	{
		free(output);
		output = execute_command(commands[i], path);
		if (commands[i + 1])
			std__write_in(output);
		i++;
	}
	return (output);
}

void	pipex(char *infile_name, char **commands, char *outfile_name, char *path)
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
	output = execute_commands(commands, path);
	if (access(outfile_name, W_OK) == -1)
	{
		free(output);
		ft_exit_error(outfile_name, 1);
	}
	outfile_fd = open(outfile_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (!outfile_fd)
		ft_error(outfile_name);
	ft_fprintf(outfile_fd, output);
	close(outfile_fd);
	free(output);
}
