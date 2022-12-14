/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:10:36 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/14 20:18:04 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	*reset_command(t_command *command)
{
	command->argv = NULL;
	command->envp = NULL;
	command->index = -1;
	command->name = NULL;
	command->process = -1;
	return (command);
}

t_command	*free_command(t_command *command)
{
	ft_free_matrix(command->argv);
	free(command->name);
	reset_command(command);
	return (command);
}

t_commands	*free_commands(t_commands *commands)
{
	unsigned int	i;

	i = 0;
	while (i < commands->length)
	{
		free_command(&commands->self[i]);
		i++;
	}
	free(commands->self);
	return (commands);
}
