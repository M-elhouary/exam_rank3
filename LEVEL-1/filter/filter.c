#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 1

int ft_strncmp(char *s1, char *s2, int len)
{
	int i = 0;
	while (s1[i] && s2[i] && i < len)
	{
		if (s1[i] > s2[i])
		{
			return (1);
		}
		else if (s1[i] < s2[i])
		{
			return (-1);
		}
		else
			i++;
	}
	return (0);
}
char *gnl(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int r;
	static int pos;
	char *line = malloc(1000000);
	int i = 0;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return NULL;

	while (1)
	{
		if (pos >= r)
		{
			r = read(fd, buffer, BUFFER_SIZE);
			pos = 0;
			if (r <= 0)
				break;
		}
		line[i++] = buffer[pos++];
		if (line[i - 1] == '\n')
			break;
	}
	line[i] = '\0';
	if (i == 0)
	{
		free(line);
		return NULL;
	}
	return line;
}

int main(int argc, char **argv)
{
	if (argc != 2 || strlen(argv[1]) == 0)
		return 1;
	char *pattern = argv[1];
	size_t pat_len = strlen(pattern);
	char *line;

	while ((line = gnl(0)) != NULL)  // read from stdin
	{
		char *p = line;
		while (*p)
		{
			if (ft_strncmp(p, pattern, pat_len) == 0)
			{
				for (size_t i = 0; i < pat_len; i++)
					write(1, "*", 1);
				p += pat_len;
			}
			else
				write(1, p++, 1);
		}
		free(line);
	}
	return 0;
}
