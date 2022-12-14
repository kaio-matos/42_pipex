/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:30:47 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/13 21:19:52 by kmatos-s         ###   ########.fr       */
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
