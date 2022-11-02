/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaio <kaio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:03:01 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/01 21:17:18 by kaio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	validate_input(int argc, char **argv);

int	main(int argc, char **argv, char **envp)
{
	validate_input(argc, argv);
	execve("/bin/ls", argv, envp);
	return (0);
}

void	validate_input(int argc, char **argv)
{
	if (argc != 5)
		ft_throw_error("Please insert four arguments.");
	if (!argv)
		ft_throw_error("Bad argument.");
}
