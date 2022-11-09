/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/08 22:04:07 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	try_to_execute(void)
{
	int	result;

	ft_printf("g__enviroment()->command.name: %s\n", g__enviroment()->command.name);
	ft_printf("g__enviroment()->command.argv: ");
	ft_printf_mtx(g__enviroment()->command.argv);
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
		dup2(p[1], STDOUT_FILENO);
		STDOUT = dup(STDOUT_FILENO);
		return (p[1]);
	}
	dup2(STDOUT, STDOUT_FILENO);
	close(STDOUT);
	close(p[1]);
	return (-1);
}

void	pipex(char *infile_name, char **commands, char *outfile_name, char *path)
{
	char	*infile;
	int		read_pipede;

	infile = ft_read_file(infile_name);
	g__enviroment()->command = parse_command_string(commands[0], path);
	// read_pipede = switch_stdout_write(1);
	ft_throw_to_child(&try_to_execute);
	// switch_stdout_write(0);
	// ft_printf(ft_read_file_fd(read_pipede));
}
