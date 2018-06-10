#include "lem_in.h"

void struct_nulling(t_params *params)
{
	(*params).buf = NULL;
	(*params).ants = 0;
	(*params).step = 0;
	(*params).links_count = 0;
	(*params).start = NULL;
  (*params).end = NULL;
}

void	list_push_back(t_list **begin_list, char *content)
{
	t_list	*list;
	t_list	*oneelem;

	list = *begin_list;
	oneelem = ft_lstnew(content, ft_strlen(content));
	oneelem->next = NULL;
	if (!list)
	{
		*begin_list = oneelem;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = oneelem;
}

int	room_push_back(t_room_list **begin_list, t_params *params, int which_room)
{
	int i;
	t_room	*oneelem;

	t_room_list	*list;
	t_room_list *link;
	i = 0;
	oneelem = NULL;
	list = *begin_list;
	if (!(link = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	if (!(oneelem = (t_room *)malloc(sizeof(t_room))))
		return (0);
	link->next = NULL;
	link->room = oneelem;
	while ((*params).buf[i] && (*params).buf[i] != ' ')
		i++;
	oneelem->which_room = which_room;
	oneelem->distance = 0;
	oneelem->links = NULL;
	oneelem->enter = NULL;
	oneelem->usage = 0;
	oneelem->name = ft_strsub((*params).buf, 0, i++);
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		oneelem->x = ft_atoi(&params->buf[i]);
	else
		return (0);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i++] != ' ')
		return (0);
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		oneelem->y = ft_atoi(&params->buf[i]);
	else
		return(0);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if (i != (int)ft_strlen((*params).buf))
		return(0);
	if (!(*begin_list))
	{
		*begin_list = link;
		return (1);
	}
	while ((*begin_list)->next)
		(*begin_list) = (*begin_list)->next;
	(*begin_list)->next = link;
	*begin_list = list;
	while (list)
	{
		ft_printf("name%s x%d y%d dist%d\n", (list)->room->name,
			(list)->room->x, (list)->room->y, (list)->room->which_room);
		list = list->next;
	}
	return (1);
}

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (new && alst && *alst)
		new->next = *alst;
	*alst = new;
}

/*int	queue_push_back(t_room_list *queue, t_params *params, t_room_list *to_add, t_room *enter)
{
	t_room	*oneelem;
	t_room_list	*list;
	t_room_list *link;

	oneelem = NULL;
	list = queue;
	if (!(link = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	if (!(oneelem = (t_room *)malloc(sizeof(t_room))))
		return (0);
	link->next = NULL;
	link->room = oneelem;
	oneelem = to_add->room;
	oneelem->usage = 1;
	oneelem->distance = (*params).step++;
	oneelem->enter = enter;
	if (oneelem->which_room == END_ROOM)
		return (2);
	list = queue;
	while (list->next)
		list = list->next;
	list->next = link;
	list = queue;
	while (list)
	{
		ft_printf("NEWWW%s x%d y%d dist%d\n", (list)->room->name,
			(list)->room->x, (list)->room->y, (list)->room->which_room);
		list = list->next;
	}
	return (1);
}*/

void	queue_push_back(t_room_list *queue, t_room_list *new)
{
	t_room_list	*list;
	t_room_list	*oneelem;

	list = queue;
	oneelem = NULL;
	oneelem->next = NULL;
	oneelem = new;
	if (!list)
	{
		list = oneelem;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = oneelem;
}

int add_to_queue(t_room_list *queue, t_params *params)
{
	ft_printf("startstart %s x%d y%d dist%d %s usage%d\n", (queue)->room->name,
		(queue)->room->x, (queue)->room->y, (queue)->room->which_room, queue->room->enter->name,
		queue->room->usage);
	t_room_list *links;
	t_room *enter;
	t_room_list *end;
	t_room_list *new;

	new = NULL;
	enter = queue->room;
	links = queue->room->links;
	end = queue;
	while (end->next)
				end = end->next;
	if (links)
		enter->usage = 2;
	while (links)
	{
		if (links->room->usage == 0)
		{
			//if (queue_push_back(queue, params, links, enter) == 2)
				//return (0);
			ft_printf("TTT%d\n", links->room->usage);
			if (!(new = (t_room_list *)malloc(sizeof(t_room_list))))
				return (0);
				new->next = NULL;
				new = links;
				new->room->usage = 1;
				new->room->distance = (*params).step++;
				new->room->enter = enter;
				ft_printf("add %s x%d y%d dist%d %s %d\n", links->room->name,
					links->room->x, links->room->y, links->room->which_room, links->room->enter->name,
				links->room->usage);
				end->next = new;
				end = end->next;
				//queue_push_back(queue, new);
				if (new->room->which_room == END_ROOM)
					return (0);
		}
		links = links->next;
	}
	return (1);
}

void create_path(t_ways *all_paths, t_room_list *queue)
{
	t_ways *new;
	t_ways *new_head;
	t_room_list *tmp_queue;

	new = NULL;
	if (!(new = (t_ways *)malloc(sizeof(t_ways))))
		return ;
	//new = NULL;
	//new->next = NULL;
	new_head = NULL;
	tmp_queue = queue;
	while (tmp_queue->next)
		tmp_queue = tmp_queue->next;
	/*while (all_paths->next)
		all_paths = all_paths->next;*/
	while (tmp_queue->room->which_room != 1)
	{
		if (!(new = (t_ways *)malloc(sizeof(t_ways))))
			return ;
		ft_printf("path%s\n", tmp_queue->room->name);
		new->name = tmp_queue->room->name;
		tmp_queue->room->usage = 3;
		new->next = new_head;
		new_head = new;
		ft_printf("2path%s\n", new->name);
		//new = new->next;
		tmp_queue->room = tmp_queue->room->enter;
	}
	if (!(new = (t_ways *)malloc(sizeof(t_ways))))
		return ;
		new->name = tmp_queue->room->name;
		tmp_queue->room->usage = 3;
		new->next = new_head;
		new_head = new;
	ft_printf("22path%s\n", new->name);
	ft_printf("path%s\n", tmp_queue->room->name);
	new = new_head;
	while (new)
	{
		ft_printf("rev%s\n", "rev");
		ft_printf("3path%s\n", new->name);
		new = new->next;
	}
	all_paths->way = new_head;
	all_paths->next = NULL;
	/*while (all_paths->way)
	{
		ft_printf("rev%s\n", "rev");
		ft_printf("3path%s\n", all_paths->way->name);
		all_paths->way = all_paths->way->next;
	}*/
}

/*int add_multiply_ways(t_ways *all_paths, t_room_list *rooms, t_params *params)
{
	t_room_list *tmp_queue;
	t_room_list *queue;
	t_room_list *tmp_rooms;

	queue = NULL;
	tmp_queue = NULL;
	tmp_rooms = rooms;
	//tmp_queue = tmp_queue->next;
	ft_printf("2mult%s\n", "mult");
	(*params).step = 0;
	if (!(queue = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	tmp_queue = queue;
	while (tmp_rooms->room->which_room != START_ROOM)
		tmp_rooms = tmp_rooms->next;
	tmp_queue->room = tmp_rooms->room;
	tmp_queue->next = NULL;
	tmp_queue->room->distance = (*params).step++;
	tmp_queue->room->usage = 1;
	tmp_queue->room->enter = tmp_queue->room;
	tmp_rooms = rooms;
	ft_printf("3mult%s\n", "mult");
	while (tmp_rooms)
	{
		if (tmp_rooms->room->usage != 3 && tmp_rooms->room->which_room != 1)
		{
			tmp_rooms->room->usage = 0;
			tmp_rooms->room->distance = 0;
			tmp_rooms->room->enter = NULL;
		}
		tmp_rooms = tmp_rooms->next;
	}
	tmp_rooms = rooms;
	ft_printf("4mult%s\n", "mult");
	while (tmp_queue)
	{
		ft_printf("5mult%s\n", "mult");
		if (!add_to_queue(tmp_queue, params))
			break ;
		ft_printf("5mult%s\n", "mult");
		tmp_queue = tmp_queue->next;
	}
	tmp_queue = queue;
	ft_printf("7mult%s\n", "mult");
	while (tmp_queue)
	{
		ft_printf("2queue%s x%d y%d whichroom%d usage%d dist%d enter%s\n", (tmp_queue)->room->name,
			(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room,
		(tmp_queue)->room->usage, (tmp_queue)->room->distance, tmp_queue->room->enter->name);
		//if ((tmp_queue)->room->which_room != 1)
			//ft_printf("enter %s\n", tmp_queue->room->enter->name);
		tmp_queue = tmp_queue->next;
	}
	ft_printf("7mult%s\n", "mult");
	if (!(all_paths = (t_ways *)malloc(sizeof(t_ways *))))
		return (0);
	ft_printf("7mult%s\n", "mult");
	create_path(all_paths, tmp_queue);
	return (1);
}*/

int search_way(t_room_list *rooms, t_params *params)
{
	int count;

	t_room_list *queue;
	t_room_list *tmp_queue;
	t_room_list *tmp_rooms;
	t_ways *all_paths;

	count = 0;
	queue = NULL;
	tmp_rooms = rooms;
	all_paths = NULL;
	tmp_queue = queue;
	if (!(queue = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	queue->next = NULL;
	while (tmp_rooms->room->which_room != START_ROOM)
		tmp_rooms = tmp_rooms->next;
	//tmp_queue = queue;
	queue->room = tmp_rooms->room;
	queue->room->distance = (*params).step++;
	queue->room->usage = 1;
	queue->room->enter = queue->room;
	tmp_rooms = rooms;
	tmp_queue = queue;

	while (tmp_queue)
	{
		if (tmp_queue->room->usage != 2)
		{
			if (!add_to_queue(tmp_queue, params))
				break ;
		}
		ft_printf("2queue%s x%d y%d whichroom%d usage%d dist%d enter%s\n", (tmp_queue)->room->name,
			(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room,
		(tmp_queue)->room->usage, (tmp_queue)->room->distance, tmp_queue->room->enter->name);
		tmp_queue = tmp_queue->next;
	}
	tmp_queue = queue;
	/*if (tmp_queue)
		return (0);*/
	while (tmp_queue)
	{
		ft_printf("2queue%s x%d y%d whichroom%d usage%d dist%d enter%s\n", (tmp_queue)->room->name,
			(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room,
		(tmp_queue)->room->usage, (tmp_queue)->room->distance, tmp_queue->room->enter->name);
		tmp_queue = tmp_queue->next;
	}
	tmp_queue = queue;
	if (!(all_paths = (t_ways *)malloc(sizeof(t_ways *))))
		return (0);
	create_path(all_paths, tmp_queue);
	/*if ((*params).ants > 1)
		{
			while (queue)
			{
				free(queue);
				queue = queue->next;
			}
			ft_printf("1mult%s\n", "mult");
			while (add_multiply_ways(all_paths, rooms, params) || (*params).ants != count)
			{
				ft_printf("1mult%s\n", "mult");
				count++;
			}
		}*/
	return (1);
}

int	make_link(t_room_list *begin_list, t_params *params)
{
	int i;
	t_room_list	*list;
	t_room	*link;
	t_room	*head;
	t_room_list	*tmplist;
	char *first;
	char *second;
	//int if_present;

	i = 0;
	head = NULL;
	link = NULL;
	tmplist = NULL;
	//if_present = 0;
	if ((*params).buf[0] == '#' || !ft_strchr((*params).buf, '-'))
		return (0);
	while ((*params).buf[i] && (*params).buf[i] != '-')
		i++;
	first = ft_strsub((*params).buf, 0, i);
	i++;
	if (!(*params).buf[i])
		return (0);
	second = ft_strsub((*params).buf, i, ft_strlen((*params).buf - 1 + 1));
	list = begin_list;
	while (list)
	{
		if (ft_strcmp(list->room->name, first) == 0)
			head = list->room;
		if (ft_strcmp(list->room->name, second) == 0)
			link = list->room;
		list = list->next;
	}
	if (!head || !link)
		return (0);
	if (!(tmplist = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	tmplist->next = head->links;
	head->links = tmplist;
	tmplist->room = link;
	if (!(tmplist = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	tmplist->next = link->links;
	link->links = tmplist;
	tmplist->room = head;
		list = begin_list;
		while (list)
		{
			tmplist = list->room->links;
			ft_printf("1head%s x%d y%d dist%d\n", (list)->room->name,
				(list)->room->x, (list)->room->y, (list)->room->which_room);
			while (tmplist)
			{
				ft_printf("1links%s x%d y%d dist%d\n", tmplist->room->name,
					tmplist->room->x, tmplist->room->y, tmplist->room->which_room);
				tmplist = tmplist->next;
			}
			list = list->next;
		}
	return (1);
}

int if_room(t_params *params, t_room_list **rooms, int which_room)
{
	//ft_printf("%s \n", "test2");
	//ft_printf("if_room%s \n", *buf);
	if ((*params).buf[0] != '#' && ft_strchr((*params).buf, ' ') &&
	ft_strcmp((*params).buf, "\n") != 0 && (*params).buf[0] != 'L')
	{
		if (ft_strchr((*params).buf, '-'))
		{
			ft_strdel(&params->buf);
			ft_printf("%s\n", "ERROR1");
			return (0);
		}
		if (!room_push_back(rooms, params, which_room))
		{
			ft_strdel(&params->buf);
			ft_printf("%s\n", "ERROR2");
			return (0);
		}
		ft_printf("buf1 %s\n", (*params).buf);
		ft_strdel(&params->buf);
		return (1);
	}
	return (0);
}

int comments_parsing(t_params *params, int *ifstart, int *ifend, t_room_list **rooms)
{
	if ((*params).buf[0] == '#' && (*params).buf[1] != '#' /*&& !ft_strchr(*buf, ' ') && !ft_strchr(*buf, '-')*/)
	{
			ft_printf("buf2 %s\n", (*params).buf);
			ft_strdel(&params->buf);
			return(1);
	}
	if (params->buf[0] == '#' && (*params).buf[1] == '#' && !ft_strstr(&params->buf[2], "start") && !ft_strstr(&params->buf[2], "end"))
	{
		ft_printf("buf3 %s\n", (*params).buf);
		ft_strdel(&params->buf);
		return(1);
	}
	if ((*params).buf[0] == '#' && (*params).buf[1] == '#' && (ft_strstr(&params->buf[2], "start") || ft_strstr(&params->buf[2], "end")))
	{
		if (ft_strstr(&params->buf[2], "start"))
		{
			if (*ifstart != 0)
			{
				ft_printf("%s\n", "ERROR3");
				ft_strdel(&params->buf);
				return (0);
			}
			else
			{
				(*ifstart) = 1;
				ft_printf("buf4 %s\n", (*params).buf);
				ft_strdel(&params->buf);
				get_next_line(0, &params->buf);
				if (!if_room(params, rooms, START_ROOM))
					return(0);
				//ft_printf("buf5 %s\n", *buf);
				return(1);
			}
		}
		if (ft_strstr(&params->buf[2], "end"))
		{
			if (*ifend != 0)
			{
				ft_printf("%s\n", "ERROR4");
				ft_strdel(&params->buf);
				return (0);
			}
			else
			{
				(*ifend) = 1;
				ft_printf("buf6 %s\n", (*params).buf);
				ft_strdel(&params->buf);
				get_next_line(0, &params->buf);
				if (!if_room(params, rooms, END_ROOM))
					return(0);
				//ft_printf("buf7 %s\n", *buf);
				return(1);
			}
		}
	}
	return(0);
}

int ants_saving(t_params *params)
{
	int i;

	i = 0;
	if ((*params).buf[0] < '1' || (*params).buf[0] > '9')
	{
		ft_strdel(&params->buf);
		ft_printf("%s\n", "ERROR5");
		return (0);
	}
	while ((*params).buf[i] > '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i])
	{
		ft_strdel(&params->buf);
		ft_printf("%s\n", "ERROR6");
		return (0);
	}
		(*params).ants = ft_atoi((*params).buf);
		ft_printf("buf8 %s\n", (*params).buf);
		ft_printf("ants %d\n", (*params).ants);
		ft_strdel(&params->buf);
		return(1);
}

int lemin_reading(t_params *params, int ifstart, int ifend, t_room_list *rooms)
{
	t_room_list *tmp_rooms;

	tmp_rooms = rooms;
	while (get_next_line(0, &params->buf) > 0)
	{
		if (ft_strcmp((*params).buf, "\n") == 0 || (*params).buf[0] == 'L')
			return (0);
		if (if_room(params, &rooms, OTHER_ROOM))
		{
			if (!(*params).links_count)
				continue ;
			else
			{
				ft_strdel(&params->buf);
				ft_printf("%s\n", "ERROR7");
				break ;
			}
		}
		if (comments_parsing(params, &ifstart, &ifend, &rooms))
			continue ;
		if (make_link(rooms, params))
		{
			(*params).links_count++;
			continue ;
		}
		ft_strdel(&params->buf);
		ft_printf("%s\n", "ERROR8");
		return (0);
	}
	search_way(rooms, params);
	while (rooms)
	{
		tmp_rooms = rooms->room->links;
		ft_printf("1head%s x%d y%d dist%d\n", (rooms)->room->name,
			(rooms)->room->x, (rooms)->room->y, (rooms)->room->which_room);
		while (tmp_rooms)
		{
			ft_printf("1links%s x%d y%d dist%d\n", tmp_rooms->room->name,
				tmp_rooms->room->x, tmp_rooms->room->y, tmp_rooms->room->which_room);
			tmp_rooms = tmp_rooms->next;
		}
		rooms = rooms->next;
	}
	return (1);
}


int main(void)
{
	t_params params;
	int ifstart;
	int ifend;
	t_room_list *rooms;

	rooms = NULL;
	ifstart = 0;
	ifend = 0;
	rooms = NULL;
	struct_nulling(&params);
	while (get_next_line(0, &params.buf) > 0 && params.buf[0] == '#')
	{
		if (!comments_parsing(&params, &ifstart, &ifend, &rooms))
			return (0);
	}
	if (!ants_saving(&params))
		return (0);
	if (!lemin_reading(&params, ifstart, ifend, rooms))
	{
		ft_strdel(&params.buf);
		ft_printf("%s\n", "ERROR8");
		return (0);
	}
}
