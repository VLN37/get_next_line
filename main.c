#include <stdio.h>
#include "get_next_line.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;

	str = "god mode";
	fd = 0;
	while (str)
	{
		str = get_next_line(fd);
		printf("line : %s", str);
		free(str);
	}
	close (fd);
	return (1);
}
