/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:53:41 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/18 21:52:17 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	std__write_in(char *string)
{
	int	stdin_fd;

	stdin_fd = std__switch_in_scope(1);
	ft_fprintf(stdin_fd, string);
	std__switch_in_scope(0);
}
