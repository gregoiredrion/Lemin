#include "libft.h"
#include <stdio.h>

void	bleble(char *str)
{
	printf("Address function = %p\n", &str);
}

int main ()
{
	char **sstr;

	sstr = ft_strsplit("Je veux mourir :) !\n", ' ');
	printf("Address main %p\n", sstr);
	bleble(*sstr);
}
