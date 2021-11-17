/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:33:10 by wwan-taj          #+#    #+#             */
/*   Updated: 2021/11/16 13:33:16 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"

char	*createbuffer(int fd, char *initbuf, char *buffer)
{
	int		numbytes;
	char	*temp;

	numbytes = 1;
	while (numbytes != '\0')
	{
		numbytes = read(fd, initbuf, BUFFER_SIZE);
		printf("~~~~~~~~~~\n%s\n~~~~~~~~~~\n", initbuf);
		if (numbytes == 0)
			return (buffer);
		else if (numbytes < 0)
			return (NULL);
		initbuf[numbytes] = '\0';
		if (!buffer)
			buffer = ft_strdup("");
		temp = buffer;
		buffer = ft_strjoin(temp, initbuf);
		free(temp);
		temp = NULL;
		if (ft_strchr(initbuf, '\n'))
			break;
	}
	return (buffer);
}

// // This functions does two things at once. 
// It returns the remaining text without the firstline 
// while also manipulating the argument into a single
// line by placing a nul terminator just after the 
// first newline it encounters

char	*splittext(char	*text)
{
	int		i;
	char	*buffer;

	i = 0;
	while (text[i] != '\0' && text[i] != '\n')
		i++;
	buffer = ft_substr(text, i + 1, ft_strlen(text) - i);
	if (buffer[0] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	text[i + 1] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*text;
	char		*initbuf;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	initbuf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!initbuf)
		return (NULL);
	text = createbuffer(fd, initbuf, buffer);
	free(initbuf);
	initbuf = NULL;
	if (!text)
		return (NULL);
	buffer = splittext(text);
	return (text);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("t.txt", O_RDONLY);
// 	for (int i = 0; i < 5; i++)
// 	{
// 		line = get_next_line(fd);
// 		printf("%d GET NEXT LINE:\n%s\n", i, line);
// 		free(line);
// 	}
// 	return (0);
// }