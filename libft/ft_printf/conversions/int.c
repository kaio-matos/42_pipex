/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:22:03 by coder             #+#    #+#             */
/*   Updated: 2022/09/20 01:32:38 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	deal_with_i(int arg)
{
	int	printed;

	printed = 0;
	if (arg == -2147483648)
		return (ft_putstr("-2147483648"));
	if (arg < 0)
	{
		arg = arg * -1;
		printed += ft_putchar('-');
	}
	return (ft_putnbase (arg, "0123456789") + printed);
}
