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
	if (!infos)
		return (NULL);
	i = 1;
	while (i < 3)
	{
		j = 0;
		while (infos[i][j])
		{
			if (!ft_isdigit(infos[i][j]))
				return (NULL); // and free;
			j++;
			if (j > 10)
				return (NULL); // and free;
		}
		i++;
	}
	return (infos);
}

char		**verif_rooms(char *line)
{
	int		i;
	int		space;

	i = 0;
	space = 0;
	while (line[i] && !space)
	{
		if (!ft_isalpha(line[i]) && !ft_isdigit(line[i]))
		{
			if (line[i] == ' ')
			{
				i++;
				space++;
				if (!ft_isdigit(line[i]))
					return (NULL);
				break ;
			}
			else
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
				if (space > 2 || !ft_isdigit(line[i + 1]))
					return (NULL);
			}
			else
				return (NULL);
		}
		i++;
	}
	return (room_errors(ft_strsplit(line, ' ')));
/*	while (line[i])
	{
		if (!space && !ft_isalpha(line[i]) && !ft_isdigit(line[i]))
		{
			if (line[i] == ' ')
			{
				if (space && !ft_isdigit(line[i + 1]))
					return (NULL);
				space++;
			}
			else
				return (NULL);
		}

		i++;
	}*/
	if (space != 2)
		return (NULL);
	if (!ft_strsplit(line, ' '))
		return (NULL);
}

char		**verif_links(char *line)
{
	int		i;
	char	tiret;

	tiret = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_isalpha(line[i]) && !ft_isdigit(line[i]))
		{
			if (line[i] == '-')
			{
				if (tiret == 1)
					return (NULL);
				tiret++;
			}
			else
				return (NULL);
		}
		i++;
	}
	if (tiret != 1)
		return (NULL);
	return (ft_strsplit(line, '-'));
}
