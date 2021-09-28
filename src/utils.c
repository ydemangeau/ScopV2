/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <ydemange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:15:33 by ydemange          #+#    #+#             */
/*   Updated: 2021/09/24 17:55:42 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/* returns a real time microsecond timestamp since epoch */
unsigned long	usec_timestamp(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return ((unsigned long)tv.tv_sec * 1000000UL + (unsigned long)tv.tv_usec);
}

/* reads an entire file and returns a malloced string with the content */
char			*read_file(const char *filename)
{
	char	*content;
	int		fd;
	size_t	file_size;

	fd = open(filename, 'r');
	if (fd < 0)
	{
		printf("Cannot open file [%s]\n", filename);
		exit(0);
	}

	/* get file size */
	file_size = (size_t)lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	
	content = malloc(file_size + 1);
	read(fd, content, file_size);
	content[file_size] = 0;
	close(fd);
	return (content);
}

float			*load_bmp(const char *filename)
{
	unsigned char	buffer[1000];
	float			*pixels;
	int				fd;
	unsigned		offset;

	fd = open(filename, 'r');
	if (fd < 0)
	{
		printf("Cannot open file [%s]\n", filename);
		exit(0);
	}

	/* go to byte array */
	read(fd, buffer, 14);
	offset = *(unsigned *)(buffer + 10);
	lseek(fd, offset, SEEK_SET);

	pixels = malloc((1200 * 675) * 3 * sizeof(float));
	for (unsigned i = 0; i < (1200 * 675); ++i)
	{
		if (read(fd, buffer, 4) != 4)
		{
			printf("Corrupted texture %d\n", i);
			exit(0);
		}
		pixels[i * 3 + 0] = buffer[2] / 255.0f;
		pixels[i * 3 + 1] = buffer[1] / 255.0f;
		pixels[i * 3 + 2] = buffer[0] / 255.0f;
	}
	close(fd);
	return (pixels);
}
