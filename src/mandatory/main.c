/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:03:01 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/05 20:35:28 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_input(int argc, char **argv);

int	main(int argc, char **argv, char **envp)
{
	char			*infile;
	char			*outfile;
	char			**commands;
	int				offset;
	t_enviroment	program_env;

	validate_input(argc, argv);
	program_env.argc = argc;
	program_env.argv = argv;
	program_env.envp = envp;
	offset = 2;
	infile = argv[1];
	outfile = argv[argc - 1];
	commands = argv + offset;
	commands[argc - (offset + 1)] = NULL;
	pipex(infile, commands, outfile, program_env);
	return (0);
}

void	validate_input(int argc, char **argv)
{
	if (argc != 5)
		ft_exit_error("Please insert four arguments.", 1);
	if (!argv)
		ft_exit_error("Bad argument.", 1);
}
