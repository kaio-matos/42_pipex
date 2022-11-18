/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/17 21:49:18 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	int	switch_stdout_write(int active)
{
	static int	p[2];
	static int	stdout_backup;

	if (active)
	{
		if (p[READ] > 0)
			close(p[READ]);
		if (p[WRITE] > 0)
			close(p[WRITE]);
		if (pipe(p) != 0)
			ft_throw_error("Couldn't create pipe");
		stdout_backup = dup(STDOUT_FILENO);
		dup2(p[WRITE], STDOUT_FILENO);
		close(p[WRITE]);
		return (p[READ]);
	}
	dup2(stdout_backup, STDOUT_FILENO);
	close(p[READ]);
	close(stdout_backup);
	p[READ] = -1;
	p[WRITE] = -1;
	return (-1);
}

static	int	switch_stdin_write(int active)
{
	static int	p[2];
	static int	stdin_backup;

	if (active)
	{
		if (p[READ] > 0)
			close(p[READ]);
		if (p[WRITE] > 0)
			close(p[WRITE]);
		if (pipe(p) != 0)
			ft_throw_error("Couldn't create pipe");
		stdin_backup = dup(STDIN_FILENO);
		dup2(p[READ], STDIN_FILENO);
		close(p[READ]);
		return (p[WRITE]);
	}
	dup2(STDIN_FILENO, stdin_backup);
	close(p[READ]);
	close(p[WRITE]);
	close(stdin_backup);
	p[READ] = -1;
	p[WRITE] = -1;
	return (-1);
}

static	void	try_to_execute(void)
{
	int	result;

	result = execve(g__enviroment()->command.argv[0], g__enviroment()->command.argv, g__enviroment()->envp);
	if (!result)
		ft_throw_error("Couldn't execute binary");
}

char	*execute_commands(char **commands, char *path)
{
	int		i;
	int		stdin_fd;
	int		stdout_fd;
	char	*output;

	i = 0;
	output = NULL;
	while (commands[i])
	{
		free(output);
		g__enviroment()->command = parse_command_string(commands[i], path);

		stdout_fd = switch_stdout_write(1);
		ft_throw_to_child(&try_to_execute);
		free(g__enviroment()->command.name);
		ft_free_matrix(g__enviroment()->command.argv);
		output = ft_read_file_fd(stdout_fd);
		switch_stdout_write(0);

		stdin_fd = switch_stdin_write(1);
		ft_fprintf(stdin_fd, output);
		stdin_fd = switch_stdin_write(0);
		i++;
	}
	return (output);
}

void	pipex(char *infile_name, char **commands, char *outfile_name, char *path)
{
	char	*infile;
	int		outfile_fd;
	int		stdin_fd;
	char	*output;

	infile = ft_read_file(infile_name);
	if (!infile)
		ft_throw_error("Could not read file");
	stdin_fd = switch_stdin_write(1);
	ft_fprintf(stdin_fd, infile);
	switch_stdin_write(0);
	output = execute_commands(commands, path);
	outfile_fd = open(outfile_name, O_CREAT | O_WRONLY, 0664);
	if (!outfile_fd)
		ft_throw_error("File could not be created or open");
	ft_fprintf(outfile_fd, output);
	close(outfile_fd);
	free(infile);
	free(output);
}
