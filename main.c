#include "lemin.h"
/*
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
}*/

int	check_room(char *line)
{
	int i;
	int sp;

	i = 0;
	sp = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			sp++;
		if ( (sp > 1 && !ft_isdigit(line[i]) && line[i] != ' ' && line[i] != '\n') || sp > 2)
		{
			ft_printf("Bad room\n");
			return -1;
		}
		i++;
	}
	if (sp != 2)
		return (-1);
	return (0);
}

t_room *return_empty(t_room **room)
{

	free((*room)->name);
	free(*room);
	return NULL;
}

t_room *fill_room(t_room *room, int phase, char *line)
{
	int i;
	char *name;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	name = ft_strsub(line, 0,i);
	room->name = ft_strtrim(name);
	if (ft_strcmp(room->name, "") == 0)
		return return_empty(&room);
	room->full = 0;
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
	free(name);
	return room;
}

int make_room(t_room **rooms, char *line, int phase)
{
	if (check_room(line) == -1)
		return (-1);
	t_room *room = (t_room*)malloc(sizeof(t_room));

	room = fill_room(room, phase, line);	

	if (room == NULL)
		return (-1);

	if (*rooms == NULL)
	{
		*rooms = room;
		return (0);
	}
	t_room *tmp = *rooms;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = room;
	room->prev = tmp;
	return 0;
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


t_room 	*get_corresponding_room(t_room *rooms, char *str)
{
	t_room *tmp;

	tmp = rooms;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			break;
		tmp = tmp->next;
	}
	return (tmp);

}

int	check_names(char **str, char **str2, char *line)
{
	char **tab;
	
	tab = ft_strsplit(line, '-');
	if (tab[0] == NULL || tab[1] == NULL || tab[2] != NULL)
	{
		ft_printf("Bad connection\n");
		return (-1);
	}
	*str = ft_strtrim(tab[0]);
	*str2 = ft_strtrim(tab[1]);
	free(tab[0]);
	free(tab[1]);
	free(tab);
}




int	make_connect(t_room *rooms, char *line, int phase)
{
	t_room	*tmp;
	t_room	*tmp2;
	char	*str;
	char	*str2; 

	if (check_names(&str, &str2, line) == -1)
		return (-1);
	tmp = get_corresponding_room(rooms, str);
	tmp2 = get_corresponding_room(rooms, str2);
	if (ft_strcmp(tmp->name, str) != 0 || ft_strcmp(tmp2->name, str2) != 0)
	{
		ft_printf("Connection doesnt correspond to any room\n");
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
		if (line[0] != 'L')
			return make_room(rooms, line, phase);
	}
	else if (*rooms)
	{
		return make_connect(*rooms, line, phase);
	}
	else
	{
		ft_printf("No rooms\n");
		return (-1);
	}

}

void	assign_score(t_room **rooms, int score)
{
	t_connect	*con;
       
	con = (*rooms)->connects;
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
	t_room	*tmp;
       
	tmp= rooms;
	while (tmp)
	{
		if (tmp->start_end == 2)
			return tmp;
		tmp = tmp->next;
	}
	ft_printf("last room not found\n");
	return NULL;
}

int	init_path(t_room *rooms, int nb_ants)
{
	t_room *tmp;

	tmp = rooms;
	while (tmp)
	{
		if (tmp->start_end == 1)
		{
			if (tmp->score == -1)
			{
				ft_printf("No path possible\n");
				return (-1);
			}
			tmp->full = nb_ants;
			tmp->ant = nb_ants;
			break ;

		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		ft_printf("No start room\n");
		return (-1);
	}
}

void	reset_turn(t_room *rooms)
{
	t_room	*tmp;

	tmp = rooms;
	while (tmp)
	{
		tmp->moved = 0;
		tmp = tmp->next;
	}
}

void	change_values(t_room **best, t_room **tmp)
{
	(*tmp)->full -= 1;
	(*best)->full += 1;
	(*best)->ant = (*tmp)->ant;
	(*best)->moved = 1;
	if ((*tmp)->start_end == 1)
		(*tmp)->ant -= 1;
	else
		(*tmp)->ant = 0;
	ft_printf("L%d-%s ", (*best)->ant, (*best)->name);
}

void	best_move(t_connect *con, t_room *tmp)
{
	t_room	*best;
	int	move;

	move = 0	;
	best = NULL;
	while (con)
	{
		if ((con->room->full == 0 || con->room->start_end == 2) && (best == NULL || (con->room->score <= best->score)))
		{
			best = con->room;
			move = 1;
		}
		con = con->next;

	}
	if (move == 1)
	{
		move = 0;
		change_values(&best, &tmp);
	}
}

void	main_loop(t_room *rooms)
{
	t_connect	*con;
	t_room		*tmp;

	tmp = rooms;
	while (tmp)
	{
		if (tmp->start_end != 2 && tmp->full >= 1 && tmp->moved == 0)
		{
			con = tmp->connects;
			best_move(con, tmp);

		}
		tmp = tmp->next;
	}

}


void	move_ants(int nb_ants, t_room *rooms, t_room *last)
{
	int	x;
	
	x = 0;
	if (init_path(rooms, nb_ants) == -1)
		return;
	while (last->full < nb_ants)
	{
		reset_turn(rooms);
		int re = nb_ants;
		while (re > 0)
		{
			main_loop(rooms);
			re--;
		}
		ft_printf("\n");
		x++;
	}
	ft_printf("%d\n", x);
}


/*
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

   }*/

int solve_it(t_room *rooms, int nb_ants)
{
	ft_printf("\n");
	if (!rooms)
		return (0);
	t_room *last = last_room(rooms);
	if (last == NULL)
		return (0);
	assign_score(&last, 1);
	move_ants(nb_ants, rooms, last);
}

int check_ants(char *line, int nb_ants)
{
	if((nb_ants = ft_atoi(line)) == 0)
	{
		ft_printf("No ants\n");
		return (-1);
	}
	else if (nb_ants < 0)
	{
		ft_printf("Invalid number of ants\n");
		return (-1);
	}
	ft_printf("%d\n", nb_ants);
	return nb_ants;
}


int	check_phase(char *line, int *phase)
{
	if (ft_strcmp(line, "##start\n") == 0)
	{
		ft_printf("%s", line);
		*phase = 1;
		return (1);
	}
	else if (ft_strcmp(line, "##end\n") == 0)
	{
		ft_printf("%s", line);
		*phase = 2;
		return (1);
	}

}

int main()
{
	t_norm	norm;

	norm.rooms = NULL;
	norm.line = NULL;
	norm.phase = 0;
	norm.nb_ants = 0;
	while (getline(&norm.line, &norm.size, stdin) != -1)
	{
		if (norm.nb_ants == 0)
		{
			if ((norm.nb_ants = check_ants(norm.line, norm.nb_ants)) == -1)
				return (0);
			continue;
		}
		if (check_phase(norm.line, &norm.phase) == 1)
			continue;
		if (handle_line(&norm.rooms, norm.phase, norm.line) == -1)
			break;
		if (norm.line[0] && norm.line[0] != '#')
			ft_printf("%s", norm.line);
		norm.phase = 0;
	}
	return (solve_it(norm.rooms, norm.nb_ants));
}
