#include "lemin.h"

int			verif_ants(char *line)
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
		ret = ret * 10 + *line++ - 48;
	}
	return (ret);
}

char		**verif_rooms(char *line)
{
	int		i;
	int		space;

	i = 0;
	while (line[i])
	{
		if (!ft_isalpha(line[i]) && !ft_isdigit(line[i]))
		{
			if (line[i] == ' ')
			{
				if (space && !ft_isdigit(line[i]))
					return (NULL);
				space++;
				if (space > 3)
					return (NULL);
			}
			else
				return (NULL);
		}
		i++;
	}

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
	return (ft_strsplit(line, '-'));
}
