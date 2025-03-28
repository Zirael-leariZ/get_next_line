/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:33:28 by oishchen          #+#    #+#             */
/*   Updated: 2025/03/28 17:21:31 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (!joined || s1len == 0 || s2len == 0)
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
	*bytes_joined = s1len + s2len;
	return (joined);
}

char	*reset_buf(char *buf)
{
	char	*cpy_buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
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

	if (!buf)
		return (NULL);
	buf_storage = gnl_join(buf, "", &bytes_joined);
	if (!buf_storage)
		return ((NULL));
	is_nl_found = 0;
	while (is_nl_found != 1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0)
			return (free(buf_storage), NULL);
		buf[bytes_read] = '\0';
		buf_storage = gnl_join(buf, buf_storage, &bytes_joined);
		if (!buf_storage || bytes_joined == 0)
			return (free(buf_storage), NULL);
		if (buf_storage[bytes_joined - 1] == '\n')
			is_nl_found = 1;
	}
	return (buf_storage);
}

char	*get_next_line(int fd)
{
	static char	buf[1024][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0)
		return (NULL);
	if (BUFFER_SIZE <= 0)
		return (buf[fd][0] = '\0', buf[fd]);
	line = ft_fetch_word(buf[fd], fd);
	if (!line)
		return (NULL);
	reset_buf(buf[fd]);
	return (line);
}
// int main()
// {
// 	int fd = open("test.txt", O_RDWR);
// 	int fd1 = open ("test1.txt", O_RDWR);
// 	int count = 7;
// 	char	*temp;

// 	// while (count > 0)
// 	// {
// 	// 	temp = get_next_line(fd);
// 	// 	printf("RESULT: %s",temp);
// 	// 	free(temp);
// 	// 	count --;
// 	// }
// 	temp = get_next_line(fd);
// 	printf("RESULT: %s", temp);
// 	free (temp);
// 	temp = get_next_line(fd1);
// 	printf("\nRESULT: %s", temp);
// 	free(temp);
// 	temp = get_next_line(fd);
// 	printf("\nRESULT: %s", temp);
// 	free (temp);
// 	return (0);
// }