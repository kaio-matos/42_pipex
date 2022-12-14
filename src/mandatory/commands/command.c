/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:10:36 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/13 21:10:51 by kmatos-s         ###   ########.fr       */
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
