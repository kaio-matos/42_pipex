/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:02:44 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/17 21:34:01 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_file_fd(int fd)
{
	char	*file;
	char	buffer[25];
	size_t	bytes;

	file = NULL;
	ft_bzero(buffer, 25);
	bytes = read(fd, buffer, 24);
	if (!bytes)
		return (NULL);
	file = ft_strljoin(file, buffer, bytes);
	while (bytes == 24)
	{
		bytes = read(fd, buffer, 24);
		if (!bytes)
			break ;
		buffer[25] = 0;
		file = ft_strljoin(file, buffer, ft_strlen(file) + bytes);
	}
	return (file);
}
