/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:16:25 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/22 15:52:34 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, unsigned int size)
{
	size_t isrc;
	size_t idest;
	size_t result;

	idest = 0;
	isrc = 0;
	result = 0;
	while (dest[idest] != '\0')
		idest++;
	while (src[result] != '\0')
		result++;
	if (size <= idest)
		result = result + size;
	else
		result = result + idest;
	while (src[isrc] != '\0' && (idest + 1) < size)
	{
		dest[idest] = src[isrc];
		isrc++;
		idest++;
	}
	dest[idest] = '\0';
	return (result);
}
