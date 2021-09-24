/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <ydemange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:15:17 by ydemange          #+#    #+#             */
/*   Updated: 2021/09/24 17:56:27 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	init_time(t_time *time)
{
	time->last = usec_timestamp();
}

/* Vertex Array Object */
static void	init_vao(t_all *al)
{
	glGenVertexArrays(1, &al->vao);
	glBindVertexArray(al->vao);
}

/* Vertex Buffer Object */
static void	init_vbo(t_all *al)
{
    /* generate buffer */
	glGenBuffers(1, &al->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, al->vbo);

    /* copy data to buffer */
 	glBufferData(GL_ARRAY_BUFFER, al->data.vertex_size, al->data.vertex, GL_STATIC_DRAW);
	 for (unsigned i = 0;i< (al->data.vertex_size /4)/4; i++){
		printf("%f %f %f - %f\n",al->data.vertex[i*4],al->data.vertex[i*4+1],al->data.vertex[i*4+2],al->data.vertex[i*4+3]);
	 }
}

/* Element buffer Object */
static void	init_ebo(t_all *al)
{
    /* generate buffer */

	glGenBuffers(1, &al->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, al->ebo);
    /* copy data to buffer */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, al->data.element_size * 4,al->data.element, GL_STATIC_DRAW);
}


static void	init_attribute(t_all *al)
{
	al->attribute.position = (GLuint)glGetAttribLocation(al->shader.program,
		"position");
	glVertexAttribPointer(al->attribute.position, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 4, (void *)(0));
	glEnableVertexAttribArray(al->attribute.position);
	
	
	/* configuration couleur 4 valeur vertex*/
	al->attribute.color_grey = (GLuint)glGetAttribLocation(al->shader.program, "color_grey");
	glVertexAttribPointer(al->attribute.color_grey, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(al->attribute.color_grey);
	
}

void 	init_matrix(t_all *al)
{
	set_mat4_identity(al->data.matrix.model);
	
	/* set the camera to face positive Z and stand back */
	set_mat4_identity(al->data.matrix.view);
	rotate_mat4(al->data.matrix.view, 0.0f, (float)M_PI, 0.0f);
	translate_mat4(al->data.matrix.view, 0, 0, -4.5f);

	set_mat4_projection(al->data.matrix.projection,
		(float)M_PI * CAMERA_FOV / 360.0f, CAMERA_NEAR, CAMERA_FAR,
		(float)WIN_SIZEX / WIN_SIZEY);
}

/* creation des uniform avec les matrices*/
static void	init_uniform(t_all *al)
{

	/* matrices */
	al->uniform.model = glGetUniformLocation(al->shader.program,
		"model_matrix");
	glUniformMatrix4fv(al->uniform.model, 1, GL_FALSE, al->data.matrix.model);

	al->uniform.view = glGetUniformLocation(al->shader.program,
		"view_matrix");
	glUniformMatrix4fv(al->uniform.view, 1, GL_FALSE, al->data.matrix.view);
	
	al->uniform.projection = glGetUniformLocation(al->shader.program,
		"projection_matrix");
	glUniformMatrix4fv(al->uniform.projection, 1, GL_FALSE,
		al->data.matrix.projection);

	/* color blending */
	al->data.blending = 0.0;
	al->uniform.blending = glGetUniformLocation(al->shader.program,
		"blending");
	glUniform1f(al->uniform.blending, al->data.blending);
}

static void	center_model(t_all *al)
{
	float	tmpx;
	float	tmpy;
	float	tmpz;
	/* initialisation des valeur +/- infini*/
	float	min[3] = {INFINITY, INFINITY, INFINITY};
	float	max[3] = {-INFINITY, -INFINITY, -INFINITY};

	for (unsigned i = 0; i < (unsigned)al->data.vertex_size /
		(4 * sizeof(float)); ++i)
	{
		tmpx = al->data.vertex[i * 4 + 0]; /* x */
		tmpy = al->data.vertex[i * 4 + 1]; /* y */
		tmpz = al->data.vertex[i * 4 + 2]; /* z */

		/* configuration avec les valeur les plus basse des vertex */
		if (tmpx < min[0])
			min[0] = tmpx;
		if (tmpx > max[0])
			max[0] = tmpx;
		if (tmpy < min[1])
			min[1] = tmpy;
		if (tmpy > max[1])
			max[1] = tmpy;
		if (tmpz < min[2])
			min[2] = tmpz;
		if (tmpz > max[2])
			max[2] = tmpz;
	}
	/* Application des modifications au model */
	translate_mat4(al->data.matrix.model,
		-(min[0] + max[0]) / 2.0f,	/* x */
		-(min[1] + max[1]) / 2.0f,	/* y */
		-(min[2] + max[2]) / 2.0f);	/* z */
}

/* initialisation de la texture*/
static void		init_texture(t_all *al)
{
	float	*pixels;

	glGenTextures(1, &al->texture);
	glBindTexture(GL_TEXTURE_2D, al->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	pixels = load_bmp("texture.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1200, 675, 0, GL_RGB, GL_FLOAT,
		pixels);
	free(pixels);
}


void	init(t_all *al, char *filename)
{
	bzero(al, sizeof(t_all));

	/* init SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		quit(al);

    /* create SDL window */
	if (!(al->window = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY,
				WIN_SIZEX, WIN_SIZEY, SDL_WINDOW_OPENGL)))
		quit(al);

    /*Config OpenGl*/
    /* init OpenGL context, version 4.1 (adapt version to OS supported) */
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_VERSION_MAJOR) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_VERSION_MINOR) < 0)
		    quit(al);

	al->auto_rotate = 1;
	al->data.animation_status = 0;
    /* create OpenGL context */
	al->glcontext = SDL_GL_CreateContext(al->window);

	/* Parse data */
	parser(al, filename);

	init_vbo(al);
    init_vao(al);
	init_ebo(al);

	init_shader(al);
	init_matrix(al);

    init_attribute(al);
	init_texture(al);

	init_uniform(al);
	center_model(al);
	glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	init_time(&al->time);
}
