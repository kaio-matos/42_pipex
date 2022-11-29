/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spliti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:05:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/28 21:48:11 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_counter(char const *string, char c)
{
	unsigned int	counter;
	unsigned int	i;

	i = 0;
	counter = 0;
	while (string[i])
	{
		while (string[i] == c)
			i++;
		if (string[i++] == '\'')
		{
			while (string[i] != '\'')
				i++;
		}
		if (string[i] && string[i] != c)
			counter++;
		while (string[i] && string[i] != c)
			i++;
	}
	return (counter);
}

static char	**fill_rows(char **rows, unsigned int length, char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	words;

	i = 0;
	words = 0;
	while (s[i] && words < length)
	{
		j = 0;
		while (s[i] == c)
			i++;
		if (s[i] == '\'')
		{
			i++;
			while (s[i + j] != '\'')
				j++;
		}
		else
			while (s[i + j] && s[i + j] != c)
				j++;
		rows[words] = ft_substr(s, i, j);
		if (s[i + j] == '\'')
			i++;
		words++;
		i += j;
	}
	rows[words] = NULL;
	return (rows);
}

char	**ft_spliti(char *s, char c)
{
	char	**mtx;
	int		words;

	mtx = NULL;
	words = word_counter(s, c) + 1;
	mtx = malloc(sizeof(char *) * words);
	fill_rows(mtx, words, s, c);
	return (mtx);
}