/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:39:20 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/22 15:00:30 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;

	i = 0;
	while (str[i] == to_find[i] && str[i])
		i++;
	if (to_find[i] == '\0')
		return ((char *)str);
	if (str[i] == '\0')
		return (0);
	return (ft_strstr(str + 1, to_find));
}
