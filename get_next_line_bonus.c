/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:30:37 by jofelipe          #+#    #+#             */
/*   Updated: 2021/08/14 21:10:50 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//read the command line and extract the global variable
//
//program reads from fd into buf
//returns the string when you find \n

//read the buf
//allocate it with strjoin
//put the rest in a global variable if necessary
//keep reading the buf
//check if strchr

// is 0 a byte read?

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdio.h>

void	writewithprotec(char **old, char **new, char *buf, int i)
{
	char	holder;

	if (!*new)
	{
		holder = buf[i + 1];
		buf[i + 1] = '\0';
		*new = ft_strjoin(buf, "");
		buf[i + 1] = holder;
	}
	else
	{
		*old = *new;
		holder = buf[i + 1];
		buf[i + 1] = '\0';
		*new = ft_strjoin(*old, buf);
		buf[i + 1] = holder;
		free(*old);
	}
}

void	writefullbuf(char **old, char **new, char *buf, int *size)
{
	if (ft_strnchr(buf, BUFFER_SIZE, '\n'))
		*size = 0;
	if (!*new)
		*new = ft_strjoin(buf, "");
	else
	{
		*old = *new;
		*new = ft_strjoin(*old, buf);
		free(*old);
	}
	ft_bzero(buf, BUFFER_SIZE);
}

void	writepartialbuf(char **old, char **new, char *buf, int *size)
{
	int	i;

	if (ft_strnchr(buf, BUFFER_SIZE, '\n') && *size < 2147483647)
		*size = 0;
	i = 0;
	while (buf[i] != '\n' && buf[i])
		++i;
	writewithprotec(old, new, buf, i);
	++i;
	ft_memmove(&buf[0], &buf[i], BUFFER_SIZE - i);
	ft_bzero(&buf[BUFFER_SIZE - i], BUFFER_SIZE - (BUFFER_SIZE - i));
}

char	*get_next_line(int fd)
{
	static char	buf[MAX_FD + 1][BUFFER_SIZE + 1];
	char		*new;
	char		*old;
	int			size;

	if (fd > MAX_FD || fd < 0)
		return (NULL);
	size = 2147483647;
	new = NULL;
	if (*buf[fd])
		writepartialbuf(&old, &new, buf[fd], &size);
	else
		ft_bzero(buf[fd], BUFFER_SIZE);
	while (size && !*buf[fd])
	{
		size = read(fd, buf[fd], BUFFER_SIZE);
		if (size == -1)
			return (NULL);
		if (size == BUFFER_SIZE && !ft_strnchr(buf[fd], BUFFER_SIZE, '\n'))
			writefullbuf(&old, &new, buf[fd], &size);
		else if (size)
			writepartialbuf(&old, &new, buf[fd], &size);
	}
	return (new);
}
