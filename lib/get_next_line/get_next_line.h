/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:45:32 by nlewicki          #+#    #+#             */
/*   Updated: 2024/07/01 13:46:53 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

char	*get_next_line(int fd);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strdup_gnl(const char *s);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
size_t	ft_strlen_gnl(const char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);

#endif
