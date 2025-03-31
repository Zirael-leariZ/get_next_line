/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:33:28 by oishchen          #+#    #+#             */
/*   Updated: 2025/03/31 17:42:59 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ft_strlen(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if (*s == uc)
			return ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *to, const void *from, size_t len)
{
	unsigned char	*ptr;
	unsigned char	*src_cpy;

	if (!to && !from)
		return (NULL);
	ptr = (unsigned char *)to;
	src_cpy = (unsigned char *)from;
	while (len--)
		*ptr++ = *src_cpy++;
	return (to);
}

char	*ft_strdup(const char *s1)
{
	int		s1len;
	char	*dup;

	s1len = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * (s1len + 1));
	if (!dup)
		return (NULL);
	dup = ft_memcpy(dup, s1, s1len);
	dup[s1len] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *container, char const *buf)
{
	int		buf_len;
	int		container_len;
	char	*joined;

	buf_len = ft_strlen(buf);
	container_len = ft_strlen(container);
	joined = (char *)malloc(sizeof(char) * (buf_len + container_len + 1));
	if (!joined)
		return (NULL);
	ft_memcpy(joined, container, container_len);
	ft_memcpy(joined + container_len, buf, buf_len);
	joined[buf_len + container_len] = '\0';
	return (joined);
}

char	*get_pure_line(char *container)
{
	char	*result;
	int		i;

	i = 0;
	while (container[i] && container[i] != '\n')
		i++;
	if (container[i] == '\n')
		i++;
	result = (char *)malloc((i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[i] = '\0';
	while (i--)
		result[i] = container[i];
	return (result);
}

char	*reset_buf(char *buf)
{
	char	*cpy_buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cpy_buf = buf;
	while (i < BUFFER_SIZE && cpy_buf[i] != '\n')
		i++;
	i++;
	if (cpy_buf[i - 1] == '\n')
	{
		while (i < BUFFER_SIZE)
		{
			buf[j] = cpy_buf[i];
			j++;
			i++;
		}
	}
	while (j < BUFFER_SIZE)
	{
		buf[j] = '\0';
		j++;
	}
	return (buf);
}

char	*buf_free(char *buf)
{
	int	i;

	i = 0;
	if (buf)
	{
		while (i < BUFFER_SIZE)
		{
			buf[i] = '\0';
			i++;
		}
	}
	return (buf);
}

char	*get_nl_line(char *buf, char *container, int fd)
{
	int		read_bytes;
	char	*joined;
	char	*result;

	read_bytes = BUFFER_SIZE;
	// printf("the container %s and its len: %lu\n", container, strlen(container));
	while (read_bytes == BUFFER_SIZE && ft_strchr(container, '\n') == NULL)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		return (free(container), buf_free(buf), NULL);
		// printf("Bytes read: %d\n", read_bytes);
		buf[read_bytes] = '\0';
		// printf("THE CUR_BUF: %s\n", buf);
		joined = ft_strjoin(container, buf);
		if (!joined)
			return (free(container), NULL);
		// printf("THE joined: %s\n", joined);
		free(container);
		container = joined;
	}
	if (read_bytes == -1)
		buf_free(buf);
	// printf("the buf %s and its len: %lu\n", buf, strlen(buf));
	result = get_pure_line(container);
	if (!result)
		return (NULL);
	// printf("SB RESULT: %s\n", result);
	reset_buf(buf);
	// printf("the reset_buf %s and its len: %lu\n", buf, strlen(buf));
	free(container);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	buf[1024][BUFFER_SIZE + 1];
	char	*result;
	char	*line;

	if (read(fd, buf[fd], 0) < 0 || BUFFER_SIZE <= 0 || fd < 0)
		return (memset(buf[fd], '\0', ft_strlen(buf[fd])), NULL);
	line = ft_strdup(buf[fd]);
	if (!line)
		return (NULL);
	result = get_nl_line(buf[fd], line, fd);
	if (!result)
		return (free(line), NULL);
	if (result[0] == '\0' && ft_strlen(result) == 0)
		return (free(result), NULL);
	return (result);
}

// int main()
// {
// 	// int fd = open("test.txt", O_RDWR);
// 	int fd1 = open("test1.txt", O_RDWR);
// 	int i = 0;
// 	char	*temp;
// 	// printf("RESULT: %s",temp);
// 	// free(temp);
// 	while (i < 5)
// 	{
// 		temp = get_next_line(fd1);
// 		printf("RESULT: %s", temp);
// 		if (temp)
// 			free(temp);
// 		i++;
// 	}
// 	return (0);
// }