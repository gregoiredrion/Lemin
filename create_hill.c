/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:44:26 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/17 18:44:28 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_hill			*create_hill(void)
{
	t_hill		*hill;

	if (!(hill = malloc(sizeof(t_hill))))
		return (NULL);
	hill->size = 0;
	hill->rooms = NULL;
	hill->start = -1;
	hill->end = -1;
	hill->turns = -1;
	return (hill);
}
