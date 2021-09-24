/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:40:01 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/22 15:07:05 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;

	i = 0;
	while (str[i] == to_find[i] && str[i] && len > i)
		i++;
	if (to_find[i] == '\0')
		return ((char *)str);
	if (str[i] == '\0' || len == i)
		return (NULL);
	return (ft_strnstr(str + 1, to_find, (len - 1)));
}
