/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:33:02 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/08/06 16:58:26 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			check_ants(char *line)
{
	int		ret;

	ret = 0;
	if (*line == '+')
		line++;
	if (*line == '-')
		return (-1);
	while (*line)
	{
		if (!(*line >= '0' && *line <= '9'))
			return (-1);
		ret = ret * 10 + *(line)++ - 48;
	}
	return (ret);
}

static char	**room_errors(char **infos)
{
	int		i;
	int		j;
	int		sign;

	if (!infos)
		return (NULL);
	i = 1;
	while (i < 3)
	{
		sign = 0;
		j = 0;
		if (infos[i][0] == '-' || infos[i][0] == '+')
		{
			j++;
			sign = 1;
		}
		while (infos[i][j])
		{
			j++;
			if (j - sign > 10)
				return (NULL); // and free;
		}
		i++;
	}
	return (infos);
}

char		**check_rooms(char *line)
{
	int		i;
	int		space;

	i = 0;
	space = 0;
	while (line[i] && !space)
	{
		if (line[i] == ' ')
		{
			i++;
			space++;
			if (line[i] == '-' || line[i] == '+')
				i++;
			if (!ft_isdigit(line[i]))
				return (NULL);
		}
		i++;
	}
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
		{
			if (line[i] == ' ')
			{
				space++;
				if (line[i] == '-' || line[i] == '+')
					i++;
				if (space > 2 || !ft_isdigit(line[i + 1]))
					return (NULL);
			}
			else
				return (NULL);
		}
		i++;
	}
	if (space != 2)
		return (NULL);
	return (room_errors(ft_strsplit(line, ' ')));
}

char		**check_links(char *line)
{
	int		i;
	char	hyphen;

	hyphen = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
		{
			if (hyphen == 1)
				return (NULL);
			hyphen++;
		}
		i++;
	}
	if (hyphen != 1)
		return (NULL);
	return (ft_strsplit(line, '-'));
}
