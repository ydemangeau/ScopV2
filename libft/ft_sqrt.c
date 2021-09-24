/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:06:46 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/26 17:29:37 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int nb)
{
	int result;

	result = 0;
	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	while (result < 46342)
	{
		if (result * result == nb)
			return (result);
		result++;
	}
	return (0);
}
