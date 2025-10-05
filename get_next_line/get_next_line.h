/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falakus <falakus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:47:07 by austunso          #+#    #+#             */
/*   Updated: 2025/10/01 15:11:04 by falakus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

char	*i_have_one_line(int fd, char *buffer);
int		found_new_line(char *buffer);
int		ft_strlen_g(char *str);
char	*ft_strjoin_g(char *buffer, char *temp_buffer);
char	*get_new_line(char *buffer);
char	*get_new_buffer(char *buffer);
char	*get_next_line(int fd);

#endif