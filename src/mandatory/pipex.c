/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:51:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/03 21:56:55 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	int	try_to_execute(char **possible_bin_paths, char **envp);

void	pipex(char *infile_name, char **commands,
			char *outfile_name, char *path, char **envp)
{
	char	*infile;
	char	*command;
	char	**bin_paths;

	infile = ft_read_file(infile_name);
	command = commands[0];
	bin_paths = generate_possible_bin_paths(path, command);

	ft_printf("\n\n%s\n", infile_name);
	ft_printf("--\n%s--\n", infile);
	ft_printf("%s\n", commands[0]);
	ft_printf("%s\n", outfile_name);
	ft_printf("%s\n", path);

	if (!try_to_execute(bin_paths, envp))
		ft_throw_error("command not found");
}

static	int	try_to_execute(char **possible_bin_paths, char **envp)
{
	char	*argv[3] = { "command", "Argument" , NULL };
	int		result;

	while (*possible_bin_paths)
	{
		result = execve(*possible_bin_paths, argv, envp);
		possible_bin_paths++;
	}
	return (result);
}
