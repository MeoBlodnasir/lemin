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
	struct s_connect *connects;
	int score;
	int start_end;

}		t_room;


#endif
