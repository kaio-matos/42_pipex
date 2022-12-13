/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:03:01 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/12 21:07:02 by kmatos-s         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (!argv)
		ft_exit_error("Bad argument.", 1);
	if (argc != 5)
		ft_exit_error("Please insert four arguments.", 1);
	while (i < argc)
	{
		if (!argv[i][0])
		{
			ft_error_message(
				"Please insert a valid argument",
				"An empty string as argument is invalid"
				);
			exit(1);
		}
		i++;
	}
}
