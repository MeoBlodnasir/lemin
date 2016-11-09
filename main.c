#include "lemin.h"

void	print_rooms(t_room *rooms)
{
	if (rooms == NULL)
		return;
	//ft_printf("ROOM PRINT\n");
	t_room *tmp = rooms;
	t_connect *con;
	while (tmp != NULL)
	{
		//ft_printf("--------------\n");
		//ft_printf("%s (phase: %d) score: %d full %d ant %d\n", tmp->name, tmp->start_end, tmp->score, tmp->full, tmp->ant);
		if (tmp->score == -1)
		{
			//ft_printf("NO SCORE ASSIGNED\n");
			exit(0);
		}
		//ft_printf("connects with: \n");
		con = tmp->connects;
		while (con)
		{
			//ft_printf("	%s\n", con->room->name);
			con = con->next;
		}
		tmp = tmp->next;
	}
	//ft_printf("END ROOM PRINT\n");
}

t_room	*make_room(t_room *rooms, char *line, int phase)
{
	int i = 0;
	t_room *room = (t_room*)malloc(sizeof(t_room));
	room->full = 0;
	while (line[i] && line[i] != ' ')
		i++;
	char *name = ft_strsub(line, 0,i);
	room->name = ft_strtrim(name);
	free(name);
	room->next = NULL;
	room->prev = NULL;
	if (phase == 2)
		room->score = 0;
	else
		room->score = -1;
	room->connects = NULL;
	room->start_end = phase;
	room->ant = 0;
	room->moved;
	if (rooms == NULL)
		return room;
	t_room *tmp = rooms;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = room;
	room->prev = tmp;
	return rooms;
}

void	set_connection(t_room *tmp, t_room *tmp2)
{
	t_connect *con1 = (t_connect*)malloc(sizeof(t_connect));
	t_connect *con2 = (t_connect*)malloc(sizeof(t_connect));
	con1->room = tmp2;
	con2->room = tmp;
	con1->next = NULL;
	con2->next = NULL;
	t_connect *tmpcon = tmp->connects;
	if (tmp->connects == NULL)
		tmp->connects = con1;
	else
	{
		while(tmpcon->next)
			tmpcon = tmpcon->next;
		tmpcon->next = con1;
	}
	tmpcon = tmp2->connects;
	if (tmp2->connects == NULL)
		tmp2->connects = con2;
	else
	{
		while(tmpcon->next)
			tmpcon = tmpcon->next;
		tmpcon->next = con2;
	}
}


int	make_connect(t_room *rooms, char *line, int phase)
{
	char **tab = ft_strsplit(line, '-');
	t_room *tmp = rooms;
	t_room *tmp2 = rooms;
	if (tab[0] == NULL || tab[1] == NULL || tab[2] != NULL)
	{
		//ft_printf("bad connection\n");
		return -1;
	}
	char *str = ft_strtrim(tab[0]);
	char *str2 = ft_strtrim(tab[1]);
	free(tab[0]);
	free(tab[1]);
	free(tab);
	while (tmp->next)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			break;
		tmp = tmp->next;
	}
	while (tmp2->next)
	{
		if (ft_strcmp(tmp2->name, str2) == 0)
			break;
		tmp2 = tmp2->next;
	}

	if (ft_strcmp(tmp->name, str) != 0 || ft_strcmp(tmp2->name, str2) != 0)

	{
		////ft_printf("%s = %s and %s = %s\n", tmp->name, str, tmp2->name, str2);
		////ft_printf("room not found\n");
		return -1;
	}
	free(str);
	free(str2);
	set_connection(tmp, tmp2);
	return 0;
}

int	handle_line(t_room **rooms, int phase, char *line)
{
	if (line[0] == '#')
		return 0;
	if (ft_strchr(line, ' ') != NULL)
	{
		*rooms = make_room(*rooms, line, phase);
	}
	else
		return make_connect(*rooms, line, phase);

}

void	assign_score(t_room **rooms, int score)
{
	t_connect *con = (*rooms)->connects;
	while (con != NULL)
	{
		if (con->room->score > score || con->room->score == -1)
		{
			con->room->score = score;

			assign_score(&con->room, score + 1);
		}

		con = con->next;
	}

}

t_room *last_room(t_room *rooms)
{
	t_room *tmp = rooms;
	while (tmp)
	{
		if (tmp->start_end == 2)
			return tmp;
		tmp = tmp->next;
	}
	////ft_printf("last room not found\n");
	exit(0);
}


void	move_ants(int nb_ants, t_room *rooms, t_room *last)
{
	t_room *tmp;
	t_connect *con;
	t_room *best;
	int move = 0;
	rooms->full = 0;
	int ant = 1;
	int x = 0;

	tmp = rooms;
	while (tmp)
	{
		if (tmp->start_end == 1)
		{
			tmp->full = nb_ants;
			tmp->ant = nb_ants;

		}
		tmp = tmp->next;
	}
	while (last->full < nb_ants)
	{
		tmp = rooms;
		while (tmp)
		{
			tmp->moved = 0;
			tmp = tmp->next;
		}
		////ft_printf("MAIN LOOP__________\n");
		int re = nb_ants;
		while (re > 0)
		{
			tmp = rooms;
			while (tmp)
			{
				//ft_printf("looking for ants to move\n");
				if (tmp->start_end != 2 && tmp->full >= 1 && tmp->moved == 0)
				{
					//ft_printf("found an ant to move %s\n", tmp->name);
					//usleep(100000);
					con = tmp->connects;
					best = NULL;
					while (con)
					{
						//ft_printf("%s\n",con->room->name);
						//usleep(100000);
						//ft_printf("looking for candidate\n");
						//ft_printf("name %s , full %d, end %d\n", con->room->name, con->room->full, con->room->start_end);
						if ((con->room->full == 0 || con->room->start_end == 2) && (best == NULL || (con->room->score <= best->score)))
						{
							//ft_printf("found one\n");
							best = con->room;
							move = 1;
						}
						con = con->next;

					}
					if (move == 1)
					{
						move = 0;
						tmp->full -= 1;
						//ft_printf("name of now empty room %s\n", tmp->name);
						best->full += 1;
						best->ant = tmp->ant;
						best->moved = 1;
						if (tmp->start_end == 1)
							tmp->ant -= 1;
						else
							tmp->ant = 0;
						ft_printf("L%d-%s ", best->ant, best->name);
					}

				}
				tmp = tmp->next;
			}
			re--;
		}
		ft_printf("\n");
		//print_rooms(rooms);

		x++;

	}
	ft_printf("%d\n", x);

}



t_room *sort_rooms(t_room *rooms)
{
	t_room *tmp;
	t_room *tmp2;

	tmp = rooms;
	tmp2 = rooms;
	t_room *a;
	t_room *b;
	while (tmp)
	{
		tmp2 = rooms;
		while (tmp2)
		{
			if (tmp2->next && tmp2->score > tmp2->next->score)
			{
				a = tmp2;
				b = tmp2->next;
				a->next = b->next;
				b->prev = a->prev;

				if (a->next)
					a->next->prev = a;

				if (b->prev)
					b->prev->next = b;


				b->next = a;
				a->prev = b;

			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	while (rooms->prev)
		rooms = rooms->prev;
	return rooms;

}

int main()
{
	char *line = NULL;
	size_t size;
	int phase = 0;
	int nb_ants = 0;
	t_room *rooms = NULL;
	while (getline(&line, &size, stdin) != -1)
	{
		if (nb_ants == 0)
		{
			if((nb_ants = ft_atoi(line)) == 0)
			{
				////ft_printf("No ants\n");
				break;
			}
			continue;
		}
		if (ft_strcmp(line, "##start\n") == 0)
		{
			phase = 1;
			continue;
		}
		else if (ft_strcmp(line, "##end\n") == 0)
		{
			phase = 2;
			continue;
		}
		if (handle_line(&rooms, phase, line) == -1)
			break;
		phase = 0;
	}

	t_room *last = last_room(rooms);
	assign_score(&last, 1);
	//rooms = sort_rooms(rooms);
	last = last_room(rooms);
	print_rooms(rooms);
	move_ants(nb_ants, rooms, last);
}
