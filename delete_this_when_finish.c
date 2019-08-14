#include "lemin.h"

void	display_paths(t_hill *hill, t_rooms ***paths)
{
	int		i = 0;
	int		j;
	while (paths[i])
	{
		j = 0;
		while (paths[i][j])
			j++;
		printf("len path = %d\n", j);
		j = 0;
		printf("%s", hill->rooms[hill->start]->name);
		while (paths[i][j])
		{
			printf("-%s", paths[i][j]->name);
			j++;
		}
		printf("\n\n");
		i++;
	}
}
