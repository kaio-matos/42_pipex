/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/04 22:05:03 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void try_to_execute(void)
{
	execve(g__enviroment()->current_binary, g__enviroment()->argv, g__enviroment()->envp);
}

void	pipex(char *infile_name, char **commands, char *outfile_name, char *path)
{
	char	*infile;
	char	*command;

	infile = ft_read_file(infile_name);
	command = commands[0];
	g__enviroment()->current_binary = get_binary_path(path, command);
	if (!g__enviroment()->current_binary)
		ft_throw_error("command not found");
	ft_throw_to_child(&try_to_execute);
}
