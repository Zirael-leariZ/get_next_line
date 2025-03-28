/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:33:28 by oishchen          #+#    #+#             */
/*   Updated: 2025/03/28 00:35:02 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		s1L;
	int		s2L;
	int		i;

	s1L = gnl_strlen(s1);
	s2L = gnl_strlen(s2);
	joined = (char *)malloc((s1L + s2L + 1) * sizeof(char));
	if (!joined)
		return (NULL);
		i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[i - s1L])
	{
		joined[i] = s2[i - s1L];
		i++;
	}
	joined[i] = '\0';
	return (joined);
}

char	*gnl_strdup(char *buf, int *flg)
{
	char	*temp;
	int		bufL;
	int		i;

	bufL = gnl_strlen(buf);
	temp = (char *)malloc((bufL + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (i <= bufL)
	{
		temp[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
	{
		temp[i] = buf[i];
		*flg = 1;
		return (temp);
	}
	temp[i] = '\0';
	return (temp);
}
/*
	@brief		takes the buf and finds its buf[i] - i not taken string \n
	@return		the boolean \n
*/
char	*fetch_string(char *buf, int fd)
{
	int		bufL;
	char	*temp;
	char	*line;
	int		nl_found;
	int		bytes_read;

	nl_found = 0;
	while (!nl_found)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		temp = gnl_strdup(buf, &nl_found);
		if (!temp)
			return (NULL);
		line = gnl_strjoin(temp, line);
	}
	return (line);
}



char *get_next_line(int fd)
{
	char	buf[1024][BUFFER_SIZE + 1];
	char	*line;
	
	if (BUFFER_SIZE >= 0 || fd < 0 || read(fd, buf[fd], 0))
		return (NULL);
	line = fetch_string(buf[fd], fd);
	return (line);
}

/*
	i need a  function that will store the read in the buf, then it will duplicate the buf into the temp. DUPLICATE will check whether there \n  or \0 sign was met if so , it tirgers a flag that will stop the duplication and the line will be returned.
*/
int	main()
{
	int i = 0;
	int fd = open("test.txt", O_RDWR);
	char	*line = get_next_line(fd);
	while (line[i])
	{
		write(1, &line[i], 1);
		i++;
	}
	free(line);
	return (0);
}