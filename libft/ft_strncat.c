/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:19:41 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/22 15:22:30 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, int nb)
{
	int idest;
	int isrc;

	idest = 0;
	isrc = 0;
	while (dest[idest] != '\0')
		idest++;
	while (src[isrc] && isrc < nb)
	{
		dest[idest] = src[isrc];
		idest++;
		isrc++;
	}
	dest[idest] = '\0';
	return (dest);
}
