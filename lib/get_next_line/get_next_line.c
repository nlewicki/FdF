/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:47:17 by nlewicki          #+#    #+#             */
/*   Updated: 2024/06/12 12:25:21 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_search(char *save)
{
	int	i;

	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	return (i);
}

static char	*ft_read(int fd, char *save)
{
	int		read_bytes;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (free(save), NULL);
	read_bytes = 1;
	buffer[0] = '\0';
	while (!(ft_strchr_gnl(buffer, '\n')) && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buffer), free(save), NULL);
		buffer[read_bytes] = '\0';
		save = ft_strjoin_gnl(save, buffer);
		if (save == NULL)
			return (free(buffer), free(save), NULL);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*line;
	char		*tmp;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save == NULL)
		save = ft_strdup_gnl("");
	if (save == NULL)
		return (NULL);
	save = ft_read(fd, save);
	if (save == NULL)
		return (NULL);
	if (save[0] == '\0')
		return (free(save), save = NULL, NULL);
	i = ft_search(save);
	line = ft_substr_gnl(save, 0, i + 1);
	if (line == NULL)
		return (free(save), save = NULL, NULL);
	tmp = ft_substr_gnl(save, i + 1, ft_strlen_gnl(save));
	if (tmp == NULL)
		return (free(save), save = NULL, free(line), line = NULL, NULL);
	return (free(save), save = tmp, line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd;

// 	i = 0;
// 	fd = open("multiple_nlx5.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error\n");
// 		return (1);
// 	}
// 	while (i < 9)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
