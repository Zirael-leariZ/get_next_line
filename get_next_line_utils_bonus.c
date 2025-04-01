/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:43 by oishchen          #+#    #+#             */
/*   Updated: 2025/04/01 16:39:00 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	while (cpy_buf[i] && i < BUFFER_SIZE && cpy_buf[i] != '\n')
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

char	*get_nl_line(char *buf, char *container, int fd)
{
	int		read_bytes;
	char	*joined;
	char	*result;

	read_bytes = BUFFER_SIZE;
	while (read_bytes == BUFFER_SIZE && ft_strchr(container, '\n') == NULL)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (ft_memcpy(buf, "\0", 1), free(container), NULL);
		buf[read_bytes] = '\0';
		joined = ft_strjoin(container, buf);
		if (!joined)
			return (free(container), NULL);
		free(container);
		container = joined;
	}
	result = get_pure_line(container);
	if (!result)
		return (free(container), NULL);
	reset_buf(buf);
	free(container);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	buf[1024][BUFFER_SIZE + 1];
	char		*result;
	char		*container;

	if (fd < 0)
		return (NULL);
	if (BUFFER_SIZE <= 0 || read(fd, buf[fd], 0) == -1)
		return (ft_memcpy(buf[fd], "\0", 1), NULL);
	container = ft_strdup(buf[fd]);
	if (!container)
		return (NULL);
	result = get_nl_line(buf[fd], container, fd);
	if (!result)
		return (NULL);
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