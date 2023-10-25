/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:47:27 by jchapell          #+#    #+#             */
/*   Updated: 2023/10/25 00:40:59 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	size;
	int		index;
	char	**res;

	res = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !res)
		return (0);
	i = -1;
	j = 0;
	size = ft_strlen(s);
	index = -1;
	while (++i <= size)
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == size) && index >= 0)
		{
			res[j++] = word_dup(s, index, i);
			index = -1;
		}
	}
	res[j] = NULL;
	return (res);
}
