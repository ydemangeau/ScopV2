/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <ydemange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:16:37 by ydemange          #+#    #+#             */
/*   Updated: 2021/09/24 17:16:48 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GL_SILENCE_DEPRECATION

# include <OpenGL/gl3.h>
# include "SDL.h"

#include <fcntl.h>		/* open */
#include <unistd.h>		/* read, close, lseek */

#include <stddef.h> /* size_t */
#include <stdio.h>	/* printf */
#include <math.h>	/* cos, sin */
#include <string.h>	/* memcpy */

#include "libft.h"

#include <stdlib.h>	/* atoi, rand */
#include <limits.h>	/* MAX_INT */

#include <sys/time.h>

# define OPENGL_VERSION_MAJOR	4
# define OPENGL_VERSION_MINOR	1

# define WIN_TITLE "Scop"
# define WIN_SIZEX	1280
# define WIN_SIZEY	720
# define WIN_POSX	100
# define WIN_POSY	50

# define CAMERA_FOV		60.0f
# define CAMERA_NEAR	1.0f
# define CAMERA_FAR		10.0f

# define IMAGE_RESOLUTION	(1200 * 675)


typedef float	mat4[16];

typedef struct	s_keys
{
	unsigned	w:1;
	unsigned	a:1;
	unsigned	s:1;
	unsigned	d:1;
	unsigned	z:1;
	unsigned	x:1;
	unsigned	e:1;
	unsigned	r:1;
	unsigned	f:1;
	unsigned	g:1;
	unsigned	q:1;


}				t_keys;

typedef struct	s_matrix
{
	mat4	model;
	mat4	view;
	mat4	projection;
}				t_matrix;
typedef struct	s_uniform
{
	/* matrices */
	GLint	model;
	GLint	view;
	GLint	projection;

	GLint	blending;
}				t_uniform;


typedef struct	s_data
{
	GLsizeiptr	element_size;
	GLuint		*element;
	GLfloat		*vertex;
	GLsizeiptr	vertex_size;

	float		blending;	/* blend facet and texture colors */
	unsigned	animation_status;

	t_matrix	matrix;
}				t_data;

typedef struct	s_attribute
{
	GLuint	position;
	GLuint	color_grey;
}				t_attribute;

typedef struct	s_shader
{
	GLuint 			vertex;
	GLuint 			geometry;
	GLuint 			fragment;
	GLuint			program;
}				t_shader;

typedef struct	s_time
{
	/* usec timestamps */
	unsigned long	current;
	unsigned long	last;
	unsigned long	target;
	unsigned long	delta;
	float			delta_sec;
	unsigned long	elapsed; /* can lag behind real time if frame time >1sec */
	unsigned long	elapsed_frames;
}				t_time;

typedef struct	s_all
{
	/* SDL */
	SDL_Window		*window;
	SDL_GLContext	glcontext;
	/* OpenGL */
	GLuint			vao; /* Vertex Array Object */
	GLuint			vbo; /* Vertex Buffer Object */
	GLuint			ebo; /* Element Buffer Object */
	
	t_shader		shader;
	t_attribute		attribute;
	GLuint 			texture;
	t_uniform		uniform;
	t_data			data;
	t_time			time;
	t_keys			keys;
	int				auto_rotate;
}				t_all;

int				quit(t_all *al);
void			init(t_all *al, char *filename);
void			main_loop(t_all *al);

/*Shader*/
void			init_shader(t_all *al);

void			parser(t_all *al, char *filename);

/* utils */
char			*read_file(const char *filename);
unsigned long	usec_timestamp(void);

/* Matrix */
void			set_mat4_identity(mat4 mat);
void			rotate_mat4(mat4 mat, float x, float y, float z);
void			translate_mat4(mat4 mat, float x, float y, float z);
void			set_mat4_projection(mat4 mat, float fov, float near, float far, float aspect);

/* texture */
float			*load_bmp(const char *filename);

#endif
