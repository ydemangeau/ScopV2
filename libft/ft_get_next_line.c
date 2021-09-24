/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrias <fdrias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:13:32 by ydemange          #+#    #+#             */
/*   Updated: 2019/02/27 18:56:54 by fdrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		readline(char **str, int fd)
{
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!str[fd])
			str[fd] = ft_strnew(1);
		tmp = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (ret);
}

int		new_line(char **str, int len, char **line, int fd)
{
	char *tmp;

	if (str[fd][len] == '\n')
	{
		*line = ft_strsub(str[fd], 0, len);
		tmp = ft_strdup(&str[fd][len + 1]);
		free(str[fd]);
		str[fd] = tmp;
		if (str[fd][0] == '\0')
			ft_strdel(&str[fd]);
	}
	else if (str[fd][len] == '\0')
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	return (1);
}

int		ft_get_next_line(const int fd, char **line)
{
	static char		*str[255];
	int				ret;
	int				len;

	len = 0;
	if (fd < 0 || line == NULL)
		return (-1);
	ret = readline(str, fd);
	if (ret == -1)
		return (-1);
	if (ret == 0 && !str[fd])
		return (0);
	while (str[fd][len] != '\n' && str[fd][len] != '\0')
		len++;
	return (new_line(str, len, line, fd));
}
