/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <ydemange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:15:29 by ydemange          #+#    #+#             */
/*   Updated: 2021/09/24 17:37:46 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "scop.h"


static GLuint compile_shader(t_all *al, const char *filename, GLenum type)
{
	GLuint		shader;
	const char	*code;
	GLint		status;
	char		buffer[512];

	code = read_file(filename);
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, 0);

	/* compiling */
	glCompileShader(shader);
	
	/* error checking */
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		printf("[%s] shader compilation failed: [%d/1]\n", filename, status);
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		printf("Compilation log:\n%s\n", buffer);
		quit(al);
	}
	free((void *)code);
	return (shader);
}

void	init_shader(t_all *al)
{
    /* Compil shader files */
	al->shader.vertex = compile_shader(al, "shader/vertex_shader.glsl",
		GL_VERTEX_SHADER);
	al->shader.geometry = compile_shader(al, "shader/geometry_shader.glsl",
		GL_GEOMETRY_SHADER);
	al->shader.fragment = compile_shader(al, "shader/fragment_shader.glsl",
		GL_FRAGMENT_SHADER);

	/* create shader program and attach shaders */
	al->shader.program = glCreateProgram();
	printf("Program: [%d/4]\n", al->shader.program);
	glAttachShader(al->shader.program, al->shader.vertex);

	glAttachShader(al->shader.program, al->shader.geometry);

	glAttachShader(al->shader.program, al->shader.fragment);
	glBindFragDataLocation(al->shader.program, 0, "outColor");

	/* link and use shader program */
	glLinkProgram(al->shader.program);
	glUseProgram(al->shader.program);
}