/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <ydemange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:15:10 by ydemange          #+#    #+#             */
/*   Updated: 2021/09/24 17:55:39 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


void	render(t_all *al)
{
    /* Clear color */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* Draw element */
	glDrawElements(GL_TRIANGLES, (GLsizei)al->data.element_size  /	(GLsizei)sizeof(float), GL_UNSIGNED_INT, 0);
	SDL_GL_SwapWindow(al->window);
}


static void	update(t_all *al)
{
	if(al->auto_rotate == 1)
		rotate_mat4(al->data.matrix.model, 0.0f, al->time.delta_sec * 0.7f, 0.0f);
	if (al->keys.w)
		translate_mat4(al->data.matrix.view, 0, al->time.delta_sec * 2, 0);
	if (al->keys.a)
		translate_mat4(al->data.matrix.view, -al->time.delta_sec * 2, 0, 0);
	if (al->keys.s)
		translate_mat4(al->data.matrix.view, 0, -al->time.delta_sec * 2, 0);
	if (al->keys.d)
		translate_mat4(al->data.matrix.view, al->time.delta_sec * 2, 0, 0);
	if (al->keys.z)
		translate_mat4(al->data.matrix.view, 0, 0, -al->time.delta_sec * 2);
	if (al->keys.x)
		translate_mat4(al->data.matrix.view, 0, 0, al->time.delta_sec * 2);
	if (al->keys.e)
		rotate_mat4(al->data.matrix.model, al->time.delta_sec * 0.7f, 0.0f, 0.0f);
	if (al->keys.r)
		rotate_mat4(al->data.matrix.model, -al->time.delta_sec * 0.7f, 0.0f, 0.0f);
	if (al->keys.f)
		rotate_mat4(al->data.matrix.model, 0.0f, al->time.delta_sec * 0.7f, 0.0f);
	if (al->keys.g)
		rotate_mat4(al->data.matrix.model, 0.0f, -al->time.delta_sec * 0.7f, 0.0f);
	
	if (al->keys.q)
		al->data.animation_status = (al->data.animation_status < 1) ? 1 : 0;
	if (al->data.animation_status)
	{
		if (al->data.blending < 1.0f)
			al->data.blending += al->time.delta_sec * 0.8f;
	}
	else
	{
		if (al->data.blending > 0.0f)
			al->data.blending -= al->time.delta_sec * 0.8f;
	}
	/* update uniforms */
	glUniformMatrix4fv(al->uniform.model, 1, GL_FALSE, al->data.matrix.model);
	glUniformMatrix4fv(al->uniform.view, 1, GL_FALSE, al->data.matrix.view);
	glUniform1f(al->uniform.blending, al->data.blending);
	
}


static void	key_func(t_all *al, SDL_Event *event)
{
	unsigned	value;

	value = event->type == SDL_KEYDOWN ? 1 : 0;
	switch (event->key.keysym.sym)
	{
		case (SDLK_ESCAPE) : quit(al); break;
		case (SDLK_w) : al->keys.w = value; break;
		case (SDLK_a) : al->keys.a = value; break;
		case (SDLK_s) : al->keys.s = value; break;
		case (SDLK_d) : al->keys.d = value; break;
		case (SDLK_z) : al->keys.z = value; break;
		case (SDLK_x) : al->keys.x = value; break;
		case (SDLK_e) : al->keys.e = value; break;
		case (SDLK_r) : al->keys.r = value; break;
		case (SDLK_f) : al->keys.f = value; break;
		case (SDLK_g) : al->keys.g = value; break;
		case (SDLK_q) : al->keys.q = value; break;
	}
}


static void	dtime(t_all *al)
{
	al->time.current = usec_timestamp();
	if (al->time.current < al->time.target)
	{
		usleep((unsigned int)(al->time.target - al->time.current));
		al->time.current = al->time.target;
	}

	al->time.delta = al->time.current - al->time.last;
	al->time.delta > 1000000 ? al->time.delta = 1000000 : 0;
	al->time.delta_sec = al->time.delta / 1000000.0f;
	al->time.last = al->time.current;
	al->time.elapsed += al->time.delta;
	++al->time.elapsed_frames;
}



void		main_loop(t_all *al)
{
	SDL_Event	event;

	while (1)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit(al);
			if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) &&
				!event.key.repeat)
				key_func(al, &event);
		}

		update(al);
		
		render(al);
		dtime(al);

	}
}
