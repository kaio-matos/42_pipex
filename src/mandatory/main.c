/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:03:01 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/03 20:17:49 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_input(int argc, char **argv);

int	main(int argc, char **argv, char **envp)
{
	// char	*infile;
	// char	*outfile;
	char	**commands;
	char	*path;
	char	**possible_bin_paths;
	char	*executable_path;
	int		offset;

	validate_input(argc, argv);
	offset = 2;
	// infile = argv[1];
	// outfile = argv[argc - 1];
	commands = argv + offset;
	commands[argc - (offset + 1)] = NULL;

	path = get_var_from_env("PATH", envp);
	possible_bin_paths = ft_split(path, ':');
	executable_path = join_paths(possible_bin_paths[0], commands[0]);
	int res = execve(executable_path, argv, envp);
	ft_printf("COMMAND          %s\n", executable_path);
	ft_printf("EXECUTION STATUS %i\n", res);


	// while (*commands)
	// {
	// 	ft_printf("current command: %s\n", *commands);
	// 	execve(*commands, argv, envp);
	// 	commands++;
	// }

	// ft_printf("\n\nargc:     %i\n", argc);
	// ft_printf("infile:   %s\n", infile);
	// ft_printf("outfile:  %s\n", outfile);
	// ft_printf("commands: %s, %s\n", commands[0], commands[1]);
	return (0);
}

void	validate_input(int argc, char **argv)
{
	if (argc != 5)
		ft_throw_error("Please insert at least four arguments.");
	if (!argv)
		ft_throw_error("Bad argument.");
}
