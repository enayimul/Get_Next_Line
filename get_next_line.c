/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enayimul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:57:41 by enayimul          #+#    #+#             */
/*   Updated: 2019/07/06 13:06:37 by enayimul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		checker(const int fd, char **fd_arr)
{
	char	buff[BUFF_SIZE + 1];
	char	*temp;
	int		rtn;

	while (ft_strchr(fd_arr[fd], '\n') == NULL)
	{
		if ((rtn = read(fd, buff, BUFF_SIZE)) == 0)
			break ;
		buff[rtn] = '\0';
		if (!(temp = ft_strjoin(fd_arr[fd], buff)))
			return (rtn);
		free(fd_arr[fd]);
		fd_arr[fd] = temp;
	}
	return (rtn);
}

static void		shift(char **fd_arr, char **line)
{
	int		after;
	char	*pointer;
	int		len;
	char	*temp;

	if (!(pointer = ft_strchr(*fd_arr, '\n')))
		pointer = ft_strchr(*fd_arr, '\0');
	len = pointer - *fd_arr;
	*line = ft_strsub(*fd_arr, 0, len);
	after = ft_strlen(*(fd_arr) + len + 1);
	if (!(pointer))
		temp = ft_strnew(0);
	else
	{
		temp = ft_strsub(*(fd_arr) + len + 1, 0, after);
		free(*fd_arr);
		*fd_arr = temp;
	}
}

int				get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static char		*fd_arr[32];
	int				rtn;

	if (fd < 0 || read(fd, buff, 0) < 0 || !line)
		return (-1);
	if (fd_arr[fd] == NULL && !(fd_arr[fd] = ft_strnew(0)))
		return (-1);
	rtn = checker(fd, fd_arr);
	if (rtn < BUFF_SIZE && !ft_strlen(fd_arr[fd]))
		return (0);
	if (fd_arr[fd])
	{
		shift(&fd_arr[fd], line);
		return (1);
	}
	else
		return (-1);
}
