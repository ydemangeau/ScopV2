/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <ydemange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:14:59 by ydemange          #+#    #+#             */
/*   Updated: 2021/09/24 17:16:18 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int	quit(t_all *al)
{
	/* vertex and element data */
	if (al->data.vertex)
		free((void *)al->data.vertex);
	if (al->data.element)
		free((void *)al->data.element);
		
	/* SDL window and SDL */
	if (al->window)
	{
		SDL_DestroyWindow(al->window);
		SDL_Quit();
	}
	exit(0);
}


int			main(int argc, char **argv)
{
	t_all	al;

	if (argc == 2)
	{
		init(&al, argv[1]);
		main_loop(&al);
	}
	printf("Usage: ./scop filename\n");
	return (0);
}