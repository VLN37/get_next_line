/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:30:37 by jofelipe          #+#    #+#             */
/*   Updated: 2021/08/11 18:51:20 by jofelipe         ###   ########.fr       */
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

char	*ft_strnchr(const char *str, int len, int c)
{
	if (!str)
		return (NULL);
	while (len--)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}

	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		size;

	if (!s1 || !s2)
		return (NULL);
	size = (ft_strlen((char *)s1) + ft_strlen((char *)s2));
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = 0;
	return (res - size);
}

void	ft_bzero(void *ptr, size_t len)
{
	while (len-- > 0)
		*(char *)ptr++ = 0;
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*ptr;

	ptr = dest;
	if (src < dest && src + n > dest)
	{
		src = src + n - 1;
		dest = dest + n - 1;
		while (n-- > 0)
			*(char *)dest-- = *(char *)src--;
	}
	else
	{
		if (!dest && !src)
			return (NULL);
		ptr = dest;
		while (n-- > 0)
			*(char *)dest++ = *(char *)src++;
		return (ptr);
	}
	return (ptr);
}

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
	if (ft_strnchr(new, ft_strlen(new), '\n'))
		size = 0;
	while (size && !*buf)
	{
		size = read(fd, buf, BUFFER_SIZE);
		buf[size] = '\0';
		if (size == -1)
			return (NULL);
		if (size == BUFFER_SIZE && !ft_strnchr(buf, BUFFER_SIZE, '\n'))
			writefullbuf(&old, &new, buf, &size);
		else if (size == BUFFER_SIZE && ft_strnchr(buf, BUFFER_SIZE, '\n'))
			writepartialbuf(&old, &new, buf, &size);
		else if (size)
			writepartialbuf(&old, &new, buf, &size);
	}
	return (new);
}
