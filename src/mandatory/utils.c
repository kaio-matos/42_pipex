/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:30:47 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/05 20:22:55 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *message)
{
	perror(message);
}

void	ft_exit_error(char *message, int number)
{
	perror(message);
	exit(number);
}

void	ft_error_message(char *message, char *argument)
{
	ft_fprintf(2, "%s: %s\n", message, argument);
}

int	ft_chrcnt(char *string, char c)
{
	int	counter;

	counter = 0;
	while (*string)
	{
		if (*string == c)
			counter++;
		string++;
	}
	return (counter);
}

void	ft_throw_to_child(void (*f) (t_command command), t_command command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_throw_error("Error during the creation of a new process");
	if (pid == 0)
	{
		f(command);
		exit(0);
	}
	else if (wait(&status) == -1)
		ft_throw_error("PID doesn't match any process");
}
