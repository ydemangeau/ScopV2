/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <ydemange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:15:26 by ydemange          #+#    #+#             */
/*   Updated: 2021/09/24 17:41:24 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*saut de ligne */
static size_t    next_line(const char *str, size_t current)
{
	size_t	next;

	next = 0;
	while (str[current + next] != 0 && str[current + next] != '\n')
		++next;
	if (str[current + next] != 0)
		++next;
	return (next);
}

/* Skip spaces */
static size_t	next_char(const char *str, size_t current)
{
	size_t	next;

	next = 0;
	while (str[current + next] != 0 && str[current + next] == ' ')
		++next;
	return (next);
}

/* to differenciate triangles from rectangle elements */
static size_t	element_type(const char *str, size_t current)
{
	int	number_vertex;

	number_vertex = 0;
	current += next_char(str, current);
	while (str[current] != 0 && str[current] != '\n')
	{
		++number_vertex;
		while (isdigit(str[current]))
			current++;
		if (str[current] == 0 || str[current] == ' ')
			current += next_char(str, current);
		else if (str[current] == '\n')
			break ;
		else
		{
			printf("Parsing error, invalid element [%c]\n", str[current]);
			exit(0);
		}
	}
	if (number_vertex != 3 && number_vertex != 4)
	{
		printf("Parsing error, invalid element (%d vertex)\n", number_vertex);
		exit(0);
	}
	return (number_vertex == 3 ? 1 : 2);
}



void    size_configure(t_all *al, const char *content)
{
    size_t  current;

	current = 0;
	while (content[current])
	{
		switch (content[current])
		{

			case 'v' :
				++al->data.vertex_size;
				break ;
			case 'f' :
				al->data.element_size += element_type(content, current + 1);
				break ;
			case '#' :
			case 'm' :
			case 'o' :
			case 's' :
			case 'u' :
			case '\n' :
				break ;
			default :
				printf("Parsing error: invalid line >%c<\n", content[current]);
				quit(al);
		}
		current += next_line(content, current);
	}
	/* Allocation des esapaces de donnes */
	al->data.vertex_size *= 4 * sizeof(float);
	al->data.element_size *= 3 * sizeof(unsigned int);
	al->data.vertex = ft_memalloc((size_t)al->data.vertex_size +1);
	al->data.element = ft_memalloc((size_t)al->data.element_size +1);
}


void    parse_vertex(t_all *al, const char *content, size_t cur)
{
	static const float	color_palette[6] = {0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f};
	static unsigned	vertex_index = 0;

	unsigned color_index = 0;
	static unsigned color = 0;

    cur += next_char(content, ++cur);
    while (content[cur] != 0 && content[cur] != '\n')
	{
		al->data.vertex[vertex_index + color_index] = (GLfloat)atof(content + cur);
		color_index++; 
		if (content[cur] == '-')
			cur++;
		while (isdigit(content[cur]) || content[cur] == '.')
			cur++;
    	cur += next_char(content, cur);

		if (color_index > 3 || (content[cur] != 0 && content[cur] != '\n' &&
			content[cur] != '-' && !isdigit(content[cur])))
		{
			printf("Parsing error, invalid vertex (number %d)\n", color_index);
			quit(al);
		}
	}
	if (color_index != 3)
	{
		printf("Parsing error, invalid vertex (%d numbers)\n", color_index);
		quit(al);
	}
	/* Ajout de couleur aux vertex x/y/z/c */
	al->data.vertex[vertex_index + 3] = color_palette[color++ % 6];
	vertex_index +=4;
}

/* creation des element */
static void		parse_element(t_all *al, const char *str, size_t current)
{
	static unsigned	current_element = 0;
	GLuint			tmp[4];
	int				number_vertex;

	number_vertex = 0;
	current += next_char(str, ++current);
	while (str[current] != 0 && str[current] != '\n')
	{
		tmp[number_vertex] = (GLuint)atoi(str + current);
		number_vertex++;
		while (isdigit(str[current]))
			current++;
		current += next_char(str, current);
	}
	for (unsigned i = 0; i < 3; ++i)
	{
		al->data.element[current_element + i] = tmp[i] -1;
	}
	current_element += 3;
	/* Si 4 valeur cree un nouvelle element */
	if (number_vertex == 4)
	{
		for (unsigned i = 0; i < 3; ++i){
			al->data.element[current_element + i] = tmp[(i + 2) % 4] -1;
		}
		current_element += 3;
	}
}

void	parser(t_all *al, char *filename)
{
    const char*     content;
    size_t             cur;

    cur = 0;
    content = read_file(filename);
	size_configure(al, content);
    while (content[cur]) 
    {
        if (content[cur] == 'v')
        {
            parse_vertex(al, content, cur);   
        }
		else if (content[cur] == 'f')
        {
            parse_element(al, content, cur);   
        }
        cur += next_line(content, cur);
    }
	free((void *)content);
}


