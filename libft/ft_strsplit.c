/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:23:53 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/23 13:56:45 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			count_word(const char *str, char c)
{
	int i;
	int result;

	result = 0;
	i = 0;
	if (str[i] == '\0')
		return (0);
	if (str[i] != c)
		result = 1;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			if (str[i] != '\0')
				result++;
			else
			{
				return (result);
			}
		}
		i++;
	}
	return (result);
}

static int			count_letters(const char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

static int			next_word(const char *str, int i, char c)
{
	while (str[i] == c)
	{
		i++;
	}
	return (i);
}

char				**ft_strsplit(char const *s, char c)
{
	char	**index;
	int		i;
	int		j;
	int		a;

	a = 0;
	i = 0;
	if (!s)
		return (NULL);
	if (!(index = (char**)malloc(sizeof(char*) * count_word(s, c) + 1)))
		return (NULL);
	while (i < count_word(s, c))
	{
		j = 0;
		a = next_word(s, a, c);
		if (!(index[i] = (char*)malloc(sizeof(char) *
						count_letters(s + a, c) + 1)))
			return (NULL);
		while (s[a] != '\0' && s[a] != c)
			index[i][j++] = s[a++];
		index[i][j] = '\0';
		i++;
	}
	index[i] = NULL;
	return (index);
}
