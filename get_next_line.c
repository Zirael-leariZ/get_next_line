/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:33:28 by oishchen          #+#    #+#             */
/*   Updated: 2025/03/27 18:47:14 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_append(char *buf, char *line, int *flg)
{
	char	*join;
	int		bufL;
	int		lineL;
	int		i;
	
	i = 0;
	bufL = ft_strlen(buf);
	lineL = ft_strlen(line);
	join = (char *)malloc((bufL + lineL + 1) * sizeof(char));
	while (line[i])
	{
		join[i] = line[i];
		i++;
	}
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			*flg = 1;
			join[lineL + i] = buf[i];
			return (join);
		}
		join[lineL + i] = buf[i];
		i++;
	}
}

/*
	@brief		takes the buf and finds its buf[i] - i not taken string \n
	@return		the boolean \n
*/
int	nearest_free(char	**buf)
{
	int	i;
	
	i = 0;
	while (buf[i] != (NULL))
	{
		if (buf[i][0] != '\0')
			return (i);
		i++;
	}
	return (-1);
}

char *get_next_line(int fd)
{
	static char	buf[1024][BUFFER_SIZE + 1];
	char	*line;
	int		bytes_read;
	int		free_pos;
	int		is_nl_found;

	line = *buf;
	if (fd < 0 || BUFFER_SIZE < 0 ||  read(fd, buf, 0) < 0)
		return (NULL);
	is_nl_found = 0;
	while (!is_nl_found)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		free_pos = nearest_free(buf);
		if (free_pos == -1)
			return ();
		buf[free_pos][bytes_read] = '\0';
		line = ft_append(buf[free_pos], line)
		
		if (!line)
			return (NULL);

		line = ft_append(buf, line, &is_nl_found) // the function should give us 
	}
	
}

/*
	i need a  function that will store the read in the buf, then it will duplicate the buf into the temp. DUPLICATE will check whether there \n  or \0 sign was met if so , it tirgers a flag that will stop the duplication and the line will be returned.
*/
