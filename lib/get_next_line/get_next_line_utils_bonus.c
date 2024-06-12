/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:28:10 by nlewicki          #+#    #+#             */
/*   Updated: 2024/04/10 12:46:34 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	slen;
	unsigned int	ind;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		return (ft_strdup(""));
	}
	if (len > slen - start)
		len = slen - start;
	substr = malloc ((len + 1) * sizeof(char));
	ind = 0;
	if (substr == NULL)
		return (NULL);
	while (ind < len && s[start + ind] != '\0')
	{
		substr[ind] = s[start + ind];
		ind++;
	}
	substr[ind] = '\0';
	return (substr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		ind;
	char	*strjoin;

	i = ft_strlen(s1);
	ind = ft_strlen(s2);
	strjoin = malloc ((ind + i + 1) * sizeof(char));
	if (strjoin == NULL)
		return (free(s1), NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		strjoin[i] = s1[i];
		i++;
	}
	ind = 0;
	while (s2[ind] != '\0')
	{
		strjoin[i + ind] = s2[ind];
		ind++;
	}
	strjoin[i + ind] = '\0';
	return (free(s1), strjoin);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*dup;

	if (s1 == NULL)
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
		len++;
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}
