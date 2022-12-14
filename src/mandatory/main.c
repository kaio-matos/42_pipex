/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:03:01 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/13 21:29:16 by kmatos-s         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}

void	validate_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		ft_exit_error("Bad argument.", EXIT_FAILURE);
	if (argc != 5)
		ft_exit_error("Please insert four arguments.", EXIT_FAILURE);
	while (i < argc)
	{
		if (!argv[i][0])
		{
			ft_error_message(
				"Please insert a valid argument",
				"An empty string as argument is invalid"
				);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
