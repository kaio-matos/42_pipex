/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/10 22:02:45 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	try_to_execute(void)
{
	int	result;

	result = execve(g__enviroment()->command.argv[0], g__enviroment()->command.argv, g__enviroment()->envp);
	if (!result)
		ft_throw_error("Couldn't execute binary");
}

static	int	switch_stdout_write(int active)
{
	static int	p[2];
	static int	STDOUT;

	if (active)
	{
		if (pipe(p) != 0)
			ft_throw_error("Couldn't create pipe");
		STDOUT = dup(STDOUT_FILENO);
		dup2(p[1], STDOUT_FILENO);
		return (p[0]);
	}
	dup2(STDOUT, STDOUT_FILENO);
	close(p[1]);
	return (p[0]);
}


static	int	switch_stdin_write(int active)
{
	static int	p[2];

	if (active)
	{
		if (pipe(p) != 0)
			ft_throw_error("Couldn't create pipe");
		dup2(p[0], STDIN_FILENO);
		return (p[1]);
	}
	close(p[0]);
	close(p[1]);
	return (p[1]);
}

void	pipex(char *infile_name, char **commands, char *outfile_name, char *path)
{
	char	*infile;
	int		stdout_pipede;
	int		i;
	int		stdin_pipede;
	char	file[5000];

	i = 0;
	stdin_pipede = -1;
	infile = ft_read_file(infile_name);
	while (commands[i])
	{
		ft_bzero(file, 5000);
		g__enviroment()->command = parse_command_string(commands[i], path);

		switch_stdout_write(1);
		ft_throw_to_child(&try_to_execute);
		stdout_pipede = switch_stdout_write(0);

		read(stdout_pipede, file, 5000);
		stdin_pipede = switch_stdin_write(1);
		ft_putstr_fd(file, stdin_pipede);
		switch_stdin_write(0);
		i++;
	}
	read(stdout_pipede, file, 5000);
	ft_printf("%s\n",file);
}
