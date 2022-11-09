/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:30:47 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/07 21:09:40 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_throw_to_child(void (*f) (void))
{
	pid_t	pid;
	pid_t	wait;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_throw_error("Error during the creation of a new process");
	if (pid == 0)
	{
		f();
		exit(0);
	}
	else
	{
		wait = waitpid(pid, &status, WUNTRACED);
		if (wait == -1)
			ft_throw_error("PID doesn't match any process");
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			wait = waitpid(pid, &status, WUNTRACED);
			if (wait == -1)
				ft_throw_error("PID doesn't match any process");
		}
	}
}
