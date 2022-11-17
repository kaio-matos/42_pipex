/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/16 22:14:05 by kmatos-s         ###   ########.fr       */
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

void	pipex(char *infile_name, char **commands, char *outfile_name, char *path)
{
	char	*infile;
	int		i;
	int		STDIN;
	int		STDOUT;
	int		p[2];

	i = 0;
	infile = ft_read_file(infile_name);
	STDIN = switch_stdin_write(1);
	ft_fprintf(STDIN, infile);
	STDIN = switch_stdin_write(0);

	while (commands[i])
	{
		g__enviroment()->command = parse_command_string(commands[i], path);
		g__enviroment()->current = i;
		ft_printf("Command[%i]: %s\n", i, g__enviroment()->command.name);

		STDOUT = switch_stdout_write(1);

		ft_throw_to_child(&try_to_execute);
		char buf[101];
		ft_bzero(buf, 101);
		read(STDOUT, buf, 100);

		switch_stdout_write(0);
		ft_printf("\n'%s'\n", buf);
		i++;
	}
}
