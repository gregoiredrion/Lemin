/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:51:34 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/04/11 17:11:17 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_assign(char **tab_fd, char **line, int i)
{
	char	*tmp;

	if (*tab_fd && ft_strchr(*tab_fd, '\n'))
	{
		while ((*tab_fd)[i] != '\n')
			i++;
		*line = ft_strsub(*tab_fd, 0, i);
		tmp = *tab_fd;
		*tab_fd = ft_strsub(*tab_fd, i + 1, ft_strlen(*tab_fd));
		free(tmp);
		if (*tab_fd[0] == '\0')
		{
			free(*tab_fd);
			*tab_fd = NULL;
		}
		return (1);
	}
	if (*tab_fd && ft_strchr(*tab_fd, '\0') && *tab_fd[0] != '\0')
	{
		*line = ft_strdup((const char *)*tab_fd);
		free(*tab_fd);
		*tab_fd = NULL;
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*tab_fd[OPEN_MAX];
	char		buf[BUFF_SIZE_GNL + 1];
	int			ret;
	char		*tmp;

	if (fd < 0 || line == NULL || OPEN_MAX < fd)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE_GNL)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (!(tab_fd[fd]))
			tab_fd[fd] = ft_strdup((const char *)buf);
		else
		{
			tmp = tab_fd[fd];
			tab_fd[fd] = ft_strjoin(tab_fd[fd], buf);
			free(tmp);
		}
		if (ft_strchr((const char *)buf, '\n'))
			break ;
	}
	return (ft_assign(&tab_fd[fd], line, 0));
}
