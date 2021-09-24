/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:17:33 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/23 13:49:14 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	str = ft_strdup((char *)s);
	if (!str || !s || !f)
		return (NULL);
	while (str[i])
	{
		str[i] = f(str[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
