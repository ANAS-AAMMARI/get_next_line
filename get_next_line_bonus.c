/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:35:16 by aaammari          #+#    #+#             */
/*   Updated: 2021/12/10 19:02:24 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_all(char *str, int fd)
{
	char	*all;
	int		byte_read;

	all = (char *)malloc(BUFFER_SIZE + 1);
	if (!all)
		return (NULL);
	byte_read = 1;
	while (!ft_strchr(str, '\n') && byte_read != 0)
	{
		byte_read = read(fd, all, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(all), NULL);
		all[byte_read] = '\0';
		str = ft_strjoin(str, all);
	}
	return (free(all), str);
}

char	*get_line(char *str)
{
	char	*line;
	int		i;
	int		len;

	len = 0;
	i = 0;
	if (!str[len])
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*rv_old_read(char *str)
{
	char	*rec;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	rec = (char *)malloc(ft_strlen(str) - i + 1);
	if (!rec)
		return (0);
	i++;
	while (str[i])
		rec[j++] = str[i++];
	rec[j] = '\0';
	free(str);
	return (rec);
}

char	*get_next_line(int fd)
{
	static char		*s[65535];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s[fd] = read_all(s[fd], fd);
	if (s[fd] == NULL)
		return (NULL);
	line = get_line(s[fd]);
	s[fd] = rv_old_read(s[fd]);
	return (line);
}
