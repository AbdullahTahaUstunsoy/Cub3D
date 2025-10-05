/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:03:24 by austunso          #+#    #+#             */
/*   Updated: 2024/12/06 14:02:50 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*i_have_one_line(int fd, char *buffer)
{
	char	*temp_buffer;
	int		char_read;

	char_read = 1;
	temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buffer)
		return (NULL);
	while (!found_new_line(buffer) && char_read != 0)
	{
		char_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (char_read == -1)
		{
			free(buffer);
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[char_read] = '\0';
		buffer = ft_strjoin(buffer, temp_buffer);
	}
	free(temp_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[MAX_FD];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = i_have_one_line(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = get_new_line(buffer[fd]);
	buffer[fd] = get_new_buffer(buffer[fd]);
	return (line);
}
