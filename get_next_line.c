/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:30:37 by jofelipe          #+#    #+#             */
/*   Updated: 2021/08/09 00:46:13 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//read the command line and extract the global variable
//
//program reads from fd into buffer
//returns the string when you find \n

//read the buffer
//allocate it with strjoin
//put the rest in a global variable if necessary
//keep reading the buffer
//check if strchr

// is 0 a byte read?

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

char	*ft_strnchr(const char *str, int len, int c)
{
	while (*str && len--)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	i;

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

void	writefullbuffer(char **old, char **new, char *buffer)
{
	if (!*new)
		*new = ft_strjoin(buffer, "");
	else
	{
		*old = *new;
		*new = ft_strjoin(*old, buffer);
		free(*old);
	}
	ft_bzero(buffer, 42);
}

void	writepartialbuffer(char **old, char **new, char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	if (!*new)
		ft_strjoin(buffer, "");
	else
	{
		*old = *new;
		*new = ft_strjoin(*old, buffer);
		free(*old);
	}
	ft_memmove(buffer, &buffer[i], BUFFER_SIZE - i);
	buffer[BUFFER_SIZE - i] = '\0';
	printf("\npartial: %s\n", buffer);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*new;
	char		*old;
	int			size;

	size = 1;
	new = NULL;
	if (*buffer)
		new = ft_strjoin(buffer, "");
	ft_bzero(buffer, BUFFER_SIZE);
	while (size)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		buffer[size] = 0;
		if (size == BUFFER_SIZE && !ft_strnchr(buffer, BUFFER_SIZE, '\n'))
			writefullbuffer(&old, &new, buffer);
		else if (size == BUFFER_SIZE && ft_strnchr(buffer, BUFFER_SIZE, '\n'))
			writepartialbuffer(&old, &new, buffer);
		else if (size < BUFFER_SIZE && ft_strnchr(buffer, BUFFER_SIZE, '\n'))
			writepartialbuffer(&old, &new, buffer);
	}
	if (new)
		return (new);
	else
		return (NULL);
}
