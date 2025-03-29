/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:33:28 by oishchen          #+#    #+#             */
/*   Updated: 2025/03/29 17:57:08 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strjoin(char const *buf, char const *container)
{
	int		buf_len;
	int		container_len;
	char	*joined;

	if (!buf || !container)
		return (NULL);
	buf_len = ft_strlen(buf);
	container_len = ft_strlen(container);
	joined = (char *)malloc(sizeof(char) * (buf_len + container_len + 1));
	if (!joined)
		return (NULL);
	ft_memcpy(joined, buf, buf_len);
	ft_memcpy(joined + buf_len, container, container_len);
	joined[buf_len + container_len] = '\0';
	return (joined);
}

char	*get_pure_line(char *line)
{
	char	*result;
	int		i;
	
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	result = (char *)malloc((i + 1) * sizeof(char));
	result = ft_memcpy(result, line, i);
	result[i] = '\0';
	return (result);
}

char	*reset_buf(char *buf, int *flg)
{
	char	*cpy_buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	// printf("we are in reset_buf funciton\n");
	cpy_buf = buf;
	while (i < BUFFER_SIZE && cpy_buf[i] != '\n')
		i++;
	i++;
	if (cpy_buf[i - 1] == '\n')
	{
		*flg = 1;
		while (i < BUFFER_SIZE)
		{
			buf[j] = cpy_buf[i];
			j++;
			i++;
		}
	}
	while (j <= BUFFER_SIZE)
		buf[j++] = '\0';
	return (buf);
}

char	*get_raw_line(char *buf, char *container, int fd)
{
	int		read_bytes;
	char	*joined;
	int		flg_nl;

	flg_nl = 0;
	read_bytes = BUFFER_SIZE;
	while (flg_nl == 0 && read_bytes == BUFFER_SIZE)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(container), free(buf), NULL);
		buf[read_bytes] = '\0';
		// printf("THE CUR_BUF: %s\n", buf);
		joined = ft_strjoin(container, buf);
		if (!joined)
			return (free(container), NULL);
		// printf("THE joined: %s\n", joined);
		free(container);
		container = joined;
		reset_buf(buf, &flg_nl);
		// printf("THE reset buf: %s\n", buf);
	}
	// printf("RAW_LINE is finished\n");
	return (container);
}

char	*get_next_line(int fd)
{
	static char	buf[1024][BUFFER_SIZE];
	char	*line;
	char	*result;

	if (read(fd, buf[fd], 0) < 0 || BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = ft_strdup(buf[fd]);
	if (!line)
		return (NULL);
	// printf("LINE WAS DUP: %s\n", line);
	line = get_raw_line(buf[fd], line, fd);
	if (!line)
		return (NULL);
	// printf("THE RAW LINE: %s\n", line);
	result = get_pure_line(line);
	if (!result)
		return (free(line), NULL);
	// printf("THE RESULT LINE: %s\n", result);
	free(line);
	if (result[0] == '\0' && ft_strlen(result) == 0)
		return (free(result), NULL);
	return (result);
}

int main()
{
	int fd = open("test.txt", O_RDWR);
	int fd1 = open("test1.txt", O_RDWR);
	char	*temp = get_next_line(fd);
	printf("RESULT: %s",temp);
	free(temp);
	temp = get_next_line(fd1);
	printf("RESULT: %s",temp);
	free(temp);
	return (0);
}