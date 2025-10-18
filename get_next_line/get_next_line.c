/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:46:52 by austunso          #+#    #+#             */
/*   Updated: 2024/12/06 13:23:24 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		buffer = ft_strjoin_g(buffer, temp_buffer);
	}
	free(temp_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = i_have_one_line(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = get_new_line(buffer);
	buffer = get_new_buffer(buffer);
	return (line);
}
