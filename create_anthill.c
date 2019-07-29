/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_anthill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:53:54 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/29 16:33:12 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_hill			*create_anthill(void)
{
	t_hill		*anthill;

	if (!(anthill = malloc(sizeof(t_hill))))
		return (NULL);
	anthill->size = 0;
	anthill->rooms = NULL;
	anthill->start = -1;
	anthill->end = -1;
	return (anthill);
}
