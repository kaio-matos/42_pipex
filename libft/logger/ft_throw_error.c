/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_throw_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:53:08 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/01 19:55:21 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_throw_error(char	*error_message)
{
	ft_printf(SHELL_R);
	ft_printf("Error:\n%s\n", error_message);
	ft_printf(SHELL_RC);
	exit(1);
}
