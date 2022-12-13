/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spliti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:05:20 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/12 21:44:36 by kmatos-s         ###   ########.fr       */
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
		if (string[i + 1] == '\'')
		{
			i += 1;
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

static void	handle_quote(char const *string, unsigned int *i, unsigned int *j)
{
	(*i)++;
	while (string[*i + *j] != '\'')
		(*j)++;
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
			handle_quote(s, &i, &j);
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

	if (!s || !*s)
		return (NULL);
	mtx = NULL;
	words = word_counter(s, c) + 1;
	mtx = malloc(sizeof(char *) * words);
	fill_rows(mtx, words, s, c);
	return (mtx);
}
