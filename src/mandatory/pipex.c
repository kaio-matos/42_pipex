/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/14 22:06:07 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	switch_stdout_write(int active)
{
	static int	p[2];
	// static int	STDOUT;

	if (active)
	{
		close(p[READ]);
		close(p[WRITE]);
		if (pipe(p) != 0)
			ft_throw_error("Couldn't create pipe");
		// STDOUT = dup(STDOUT_FILENO);
		dup2(p[WRITE], STDOUT_FILENO);
		close(p[READ]);
		return ;
	}
	// dup2(STDOUT_FILENO, STDOUT);
	close(p[READ]);
	close(p[WRITE]);
}

static	void	switch_stdin_write(int active)
{
	static int	p[2];
	static int	STDIN;

	if (active)
	{
		close(p[READ]);
		close(p[WRITE]);
		if (pipe(p) != 0)
			ft_throw_error("Couldn't create pipe");
		STDIN = dup(STDIN_FILENO);
		dup2(p[READ], STDIN_FILENO);
		close(p[WRITE]);
		return ;
	}
	dup2(STDIN_FILENO, STDIN);
	close(p[READ]);
	close(p[WRITE]);
}

static	void	try_to_execute(void)
{
	int	result;

	if (g__enviroment()->current == 0)
	{
		switch_stdout_write(1);
		switch_stdout_write(0);
	}
	switch_stdin_write(0);
	result = execve(g__enviroment()->command.argv[0], g__enviroment()->command.argv, g__enviroment()->envp);
	if (!result)
		ft_throw_error("Couldn't execute binary");
}

void	pipex(char *infile_name, char **commands, char *outfile_name, char *path)
{
	char	*infile;
	int		i;

	i = 0;
	infile = ft_read_file(infile_name);
	while (commands[i])
	{
		g__enviroment()->command = parse_command_string(commands[i], path);
		g__enviroment()->current = i;
		switch_stdin_write(1);
		ft_throw_to_child(&try_to_execute);
		switch_stdin_write(0);
		i++;
	}
	ft_printf("STD IS NOT BROKEN\n");
}
