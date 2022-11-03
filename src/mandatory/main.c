/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:03:01 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/03 20:56:56 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_input(int argc, char **argv);

int	main(int argc, char **argv, char **envp)
{
	char	*infile;
	char	*outfile;
	char	**commands;
	char	*path;
	int		offset;

	validate_input(argc, argv);
	offset = 2;
	infile = argv[1];
	outfile = argv[argc - 1];
	commands = argv + offset;
	commands[argc - (offset + 1)] = NULL;
	path = get_var_from_env("PATH", envp);
	if (!path)
		ft_throw_error("Enviroment variable 'PATH' not found");
	pipex(infile, commands, outfile, path);
	return (0);
}

void	validate_input(int argc, char **argv)
{
	if (argc != 5)
		ft_throw_error("Please insert at least four arguments.");
	if (!argv)
		ft_throw_error("Bad argument.");
}
