#include "lemin.h"

void	print_rooms(t_room *rooms)
{
	if (rooms == NULL)
		return;
	ft_printf("ROOM PRINT\n");
	t_room *tmp = rooms;
	while (tmp->next != NULL)
	{
		ft_printf("--------------\n");
		ft_printf("%s\n", tmp->name);
		ft_printf("connects with: \n");
		while (tmp->connects->next)
		{
			ft_printf("	%s\n", tmp->connects->room->name);
			tmp->connects = tmp->connects->next;
		}
			ft_printf("	%s\n", tmp->connects->room->name);
		tmp = tmp->next;
	}
		ft_printf("--------------\n");
	ft_printf("%s\n", tmp->name);
	ft_printf("connects with: \n");
	while (tmp->connects->next)
	{
		ft_printf("	%s\n", tmp->connects->room->name);
		tmp->connects = tmp->connects->next;
	}
	ft_printf("	%s\n", tmp->connects->room->name);
	ft_printf("END ROOM PRINT\n");
}

t_room	*make_room(t_room *rooms, char *line, int phase)
{
	ft_printf("making a room\n");
	int i = 0;
	t_room *room = (t_room*)malloc(sizeof(t_room));
	room->full = 0;
	while (line[i] && line[i] != ' ')
		i++;
	char *name = ft_strsub(line, 0,i);
	room->name = ft_strtrim(name);
	free(name);
	ft_printf("name at creation %s\n", room->name);
	room->next = NULL;
	room->score = 0;
	room->connects = NULL;
	if (rooms == NULL)
		rooms = room;
	else
	{
		t_room *tmp = rooms;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = room;
	}
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
	ft_printf("making connection\n");
	char **tab = ft_strsplit(line, '-');
	ft_printf("%s - %s", tab[0], tab[1]);
	t_room *tmp = rooms;
	t_room *tmp2 = rooms;
	while (tmp->next)
	{
		ft_printf("%s\n",tmp->name);
		if (ft_strncmp(tmp->name, tab[0], ft_strlen(tmp->name)) == 0)
			break;
		tmp = tmp->next;
	}
	while (tmp2->next)
	{
		if (ft_strncmp(tmp2->name, tab[1], ft_strlen(tmp2->name)) == 0)
			break;
		tmp2 = tmp2->next;
	}

	if (ft_strncmp(tmp2->name, tab[1], ft_strlen(tmp2->name)) != 0 || ft_strncmp(tmp->name, tab[0], ft_strlen(tmp->name)) != 0)

	{
		ft_printf("%s = %s and %s = %s", tmp->name, tab[0], tmp2->name, tab[1]);
		ft_printf("room not found");
		return -1;
	}
	ft_printf("setting connection\n");
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
				ft_printf("No ants\n");
				break;
			}
			continue;
		}
		if (ft_strcmp(line, "##start") == 0)
			phase = 1;
		else if (ft_strcmp(line, "##end") == 0)
			phase = 2;
		if (handle_line(&rooms, phase, line) == -1)
			break;
		phase = 0;
		//free(line);
		ft_printf("loop\n");

	}
	print_rooms(rooms);
}
