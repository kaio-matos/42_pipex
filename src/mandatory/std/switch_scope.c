/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_scope.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:54:23 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/18 21:52:32 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	std__switch_in_scope(int active)
{
	static int	p[2];
	static int	stdin_backup;

	if (active)
	{
		if (p[READ] > 0)
			close(p[READ]);
		if (p[WRITE] > 0)
			close(p[WRITE]);
		if (pipe(p) != 0)
			ft_error("");
		stdin_backup = dup(STDIN_FILENO);
		dup2(p[READ], STDIN_FILENO);
		close(p[READ]);
		return (p[WRITE]);
	}
	dup2(STDIN_FILENO, stdin_backup);
	close(p[READ]);
	close(p[WRITE]);
	close(stdin_backup);
	p[READ] = -1;
	p[WRITE] = -1;
	return (-1);
}

int	std__switch_out_scope(int active)
{
	static int	p[2];
	static int	stdout_backup;

	if (active)
	{
		if (p[READ] > 0)
			close(p[READ]);
		if (p[WRITE] > 0)
			close(p[WRITE]);
		if (pipe(p) != 0)
			ft_error("");
		stdout_backup = dup(STDOUT_FILENO);
		dup2(p[WRITE], STDOUT_FILENO);
		close(p[WRITE]);
		return (p[READ]);
	}
	dup2(stdout_backup, STDOUT_FILENO);
	close(p[READ]);
	close(stdout_backup);
	p[READ] = -1;
	p[WRITE] = -1;
	return (-1);
}
