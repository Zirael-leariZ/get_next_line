/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:33:28 by oishchen          #+#    #+#             */
/*   Updated: 2025/03/28 06:08:37 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

	/*
	inits: buf[1024][BUFFER_MAX];
	*/
	/*
	main logic: take the buffer into the read by the fd, 
	store there the chars by the size of BUFFER_MAX,
		use a strdup for this purpose that should also take a flga of the found_nl
	join the line with some temp string
	*/

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;

	i = 0;
	while (s1[i])
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	dup[i] = '\0';
	while (i--)
		dup[i] = s1[i];
	return (dup);
}

int	gnl_len(char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*gnl_join(char *buf, char *buf_storage, int *bytes_joined)
{
	char	*joined;
	int		s1len;
	int		s2len;
	int		i;

	s1len = gnl_len(buf_storage);
	s2len = gnl_len(buf);

	joined = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < s1len)
	{
		joined[i] = buf_storage[i];
		i++;
	}
	i = 0;
	while (i - s1len < s2len)
	{
		joined[i + s1len] = buf[i];
		i++;
	}
	joined[i] = '\0';
	printf("Here is our joined: %s\n", joined);
	*bytes_joined = s1len + s2len;
	printf("The Bytes_joined: %d\n", *bytes_joined);
	return (joined);
}

char	*reset_buf(char *buf)
{
	char	*cpy_buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	printf("we are in reset_buf funciton\n");
	cpy_buf = buf;
	while (cpy_buf[i] != '\n')
		i++;
	i++;
	while (cpy_buf[i])
	{
		buf[j] = cpy_buf[i];
		j++;
		i++;
	}
	buf[j] = '\0';
	return (buf);
}

char	*ft_fetch_word(char *buf, int fd)
{
	char	*buf_storage;
	int		bytes_read;
	int		is_nl_found;
	int		bytes_joined;

	buf_storage = ft_strdup(buf);
	printf("So far buf_storage looks like : %s\n", buf_storage);
	is_nl_found = 0;
	while (is_nl_found != 1)
	{
		printf("We are in the loop\n");
		bytes_read = read(fd, buf, BUFFER_SIZE);
		printf("bytes read: %d\n", bytes_read);
		if (bytes_read <= 0)
			return (NULL);
		buf[bytes_read] = '\0';
		printf("So far buf looks like : %s\n", buf);
		buf_storage = gnl_join(buf, buf_storage, &bytes_joined);
		if (buf_storage[bytes_joined - 1] == '\n')
		{
			printf("the char buf_storage[bytes_joined - 1]: %c\n", buf_storage[bytes_joined - 1]);
			is_nl_found = 1;
			// buf = reset_buf(buf);
			// printf("buf after reset: %s\n", buf);
		}
	}
	return (buf_storage);
}

char	*get_next_line(int fd)
{
	static char	buf[1024][BUFFER_SIZE + 1];
	char	*line;

	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	line = ft_fetch_word(buf[fd], fd);
	if (!line)
		return (NULL);
	reset_buf(buf[fd]);
	printf("buf after reset: %s\n", buf[fd]);
	return (line);
}
int main()
{
	int fd = open("test.txt", O_RDWR);
	char	*temp = get_next_line(fd);
	printf("RESULT: %s",temp);
	free(temp);
	temp = get_next_line(fd);
	printf("RESULT: %s",temp);
	free(temp);
	return (0);
}