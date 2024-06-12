/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:47:17 by nlewicki          #+#    #+#             */
/*   Updated: 2024/04/10 16:23:35 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	while (!(ft_strchr(buffer, '\n')) && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buffer), free(save), NULL);
		buffer[read_bytes] = '\0';
		save = ft_strjoin(save, buffer);
		if (save == NULL)
			return (free(buffer), free(save), NULL);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[MAX_FD];
	char		*line;
	char		*tmp;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save[fd] == NULL)
		save[fd] = ft_strdup("");
	if (save[fd] == NULL)
		return (NULL);
	save[fd] = ft_read(fd, save[fd]);
	if (save[fd] == NULL)
		return (NULL);
	if (save[fd][0] == '\0')
		return (free(save[fd]), save[fd] = NULL, NULL);
	i = ft_search(save[fd]);
	line = ft_substr(save[fd], 0, i + 1);
	if (line == NULL)
		return (free(save[fd]), save[fd] = NULL, NULL);
	tmp = ft_substr(save[fd], i + 1, ft_strlen(save[fd]));
	if (tmp == NULL)
		return (free(save[fd]), save[fd] = NULL, free(line), line = NULL, NULL);
	return (free(save[fd]), save[fd] = tmp, line);
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
