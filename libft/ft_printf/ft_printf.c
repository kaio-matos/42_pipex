/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:30:47 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/15 23:39:40 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_printf(const char *str, ...)
{
	char	*result;
	int		printed;
	t_slot	finded;
	va_list	args;

	if (!str)
		return (-1);
	va_start(args, str);
	result = ft_strdup(str);
	finded = get_slot(result, 0);
	printed = deal_args(finded, args, 0, STDOUT_FILENO);
	free(result);
	va_end(args);
	return (printed);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	char	*result;
	int		printed;
	t_slot	finded;
	va_list	args;

	if (!str)
		return (-1);
	va_start(args, str);
	result = ft_strdup(str);
	finded = get_slot(result, 0);
	printed = deal_args(finded, args, 0, fd);
	free(result);
	va_end(args);
	return (printed);
}
