#version 410 core

uniform mat4	model_matrix;
uniform mat4	view_matrix;
uniform mat4	projection_matrix;

in vec3			position;

in float		color_grey;

out vec3		color_vertex;
out vec2		texture_position_vertex;

void	main()
{
	color_vertex = vec3(color_grey);
	texture_position_vertex = vec2(position.z, position.y);
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
}
