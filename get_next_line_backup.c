/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_backup.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:30:37 by jofelipe          #+#    #+#             */
/*   Updated: 2021/08/15 12:09:40 by jofelipe         ###   ########.fr       */
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

#include "get_next_line.h"
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
	ft_memmove(buf, &buf[i], BUFFER_SIZE - i);
	ft_bzero(&buf[BUFFER_SIZE - i], BUFFER_SIZE - (BUFFER_SIZE - i));
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*new;
	char		*old;
	int			size;

	size = 2147483647;
	new = NULL;
	if (*buf)
		writepartialbuf(&old, &new, buf, &size);
	else
		ft_bzero(buf, BUFFER_SIZE);
	while (size && !*buf)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1)
			return (NULL);
		if (size == BUFFER_SIZE && !ft_strnchr(buf, BUFFER_SIZE, '\n'))
			writefullbuf(&old, &new, buf, &size);
		else if (size)
			writepartialbuf(&old, &new, buf, &size);
	}
	return (new);
}
