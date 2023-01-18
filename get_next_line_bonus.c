/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:20:51 by ajeftani          #+#    #+#             */
/*   Updated: 2022/11/17 22:17:54 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_give_the_left(char *str_left)
{
	char	*str_new_lefted;
	int		i;
	int		j;

	i = 0;
	if (!str_left)
		return (NULL);
	while (str_left[i] && str_left[i] != '\n')
		i++;
	if (!str_left[i])
	{
		free(str_left);
		return (NULL);
	}
	i++;
	str_new_lefted = malloc(sizeof(char) * ft_strlen(str_left) - i + 2);
	if (!str_new_lefted)
		return (NULL);
	j = 0;
	while (str_left[i])
		str_new_lefted[j++] = str_left[i++];
	str_new_lefted[j] = '\0';
	free(str_left);
	return (str_new_lefted);
}

char	*ft_free(char *string)
{
	if (string[0] == '\0')
	{
		free(string);
		return (NULL);
	}
	return (string);
}

char	*ft_return_the_line(char *str_left)
{
	int		index;
	char	*string;

	index = 0;
	if (!str_left)
		return (NULL);
	while (str_left[index] && str_left[index] != '\n')
		index++;
	string = malloc(sizeof(char) * (index + 2));
	if (!string)
		return (NULL);
	index = 0;
	while (str_left[index] && str_left[index] != '\n')
	{
		string[index] = str_left[index];
		index++;
	}
	if (str_left[index] == '\n')
	{
		string[index] = str_left[index];
		index++;
	}
	string[index] = '\0';
	return (ft_free(string));
}

char	*ft_read_str_left(char *str, int fd)
{
	char	*buff;
	int		num;

	buff = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	num = 1;
	while (!ft_strchr(str, '\n') && num != 0)
	{
		num = read(fd, buff, BUFFER_SIZE);
		if (num == -1)
		{
			free(str);
			free(buff);
			return (NULL);
		}
		buff[num] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str_left[OPEN_MAX];
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str_left[fd] = ft_read_str_left(str_left[fd], fd);
	result = ft_return_the_line(str_left[fd]);
	str_left[fd] = ft_give_the_left(str_left[fd]);
	return (result);
}
