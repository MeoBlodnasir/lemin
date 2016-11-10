#ifndef LEMIN_H
# define LEMIN_H
# include "libft/libft.h"
# include <stdio.h>


typedef struct s_connect
{
	struct s_room *room;
	struct s_connect *next;
}		t_connect;

typedef struct s_room
{
	int full;
	char *name;
	int ant;
	int moved;
	struct s_room *next;
	struct s_room *prev;
	struct s_connect *connects;
	int score;
	int start_end;

}		t_room;
typedef struct s_norm
{
	char *line;
	size_t size;
	int phase;
	int nb_ants;
	t_room *rooms;
}		t_norm;


#endif
