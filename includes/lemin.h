/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:01:24 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/11/24 15:24:06 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define START 0
# define END 1

typedef struct		s_links
{
	struct s_rooms	*room;
	int				w;
	int				used;
	struct s_links	*next;
	struct s_links	*opp;
}					t_links;

typedef struct		s_rooms
{
	char			*name;
	int				d;
	int				index;
	int				ants;
	intmax_t		x;
	intmax_t		y;
	int				used;
	int				pred;
	int				stend;
	t_links			*links;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_hill
{
	t_rooms			**rooms;
	int				start;
	int				end;
	int				ants;
	int				size;
	double			turns;
	int				max_paths;
}					t_hill;

/*
** parse and create struct
*/
t_hill				*create_hill(void);
t_rooms				*create_rooms(t_rooms *last, char **line, int stend);
int					parse_links(t_hill *hill, char *line);
unsigned int		hash(char *str, int size);
int					hashmap(t_hill *anthill, t_rooms *begin);
int					parser(t_hill *hill, char *line);
void				from_map_to_tab(t_hill *hill, t_rooms **tab);
t_links				*create_link(t_rooms *room, t_links *opp);
t_rooms				**small_tab(t_hill *hill);
/*
** check validity
*/
int					check_ants(char *line);
char				**check_links(char *line);
char				**check_rooms(char *line);
/*
** free
*/
void				del_link(t_links **link);
void				free_links(t_links *link);
void				free_room(t_rooms **room);
void				free_hill(t_hill *anthill);
void				free_paths(t_rooms ***paths);
/*
** Algo
*/
int					prep_suurballe(t_hill *hill, t_rooms **tab);
int					suurballe(t_hill *hill, t_rooms **tab);
void				bellman_ford(t_rooms **tab, int size);
int					find_path(t_rooms **tab);
t_rooms				***all_paths(t_rooms **tab, int paths);
double				max_turns(t_hill *hill, t_rooms ***paths, int nb_paths);
int					duplicate_rooms(t_rooms ***paths);
void				new_dists(t_rooms ***paths);
/*
** Move_ants
*/
void				move_ants(t_hill *hill, t_rooms ***paths, t_rooms **tab);
int					print_direct_path(char *end, int ants);





//delete + fonction!!
void				display_tab2(t_rooms **tab);
//delete + fonction!!
void				display_tab(t_rooms **tab, int size);
//delete + fonction!!
void				display_paths(t_hill *hill, t_rooms ***paths);
//delete + fonction!!
void				display_room(t_rooms *room);
//delete + fonction!!
void				checker(t_rooms ***paths, t_rooms *start, t_rooms *end);

#endif
