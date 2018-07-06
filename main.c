#include "lem_in.h"

void struct_nulling(t_params *params)
{
	(*params).buf = NULL;
	(*params).ants = 0;
	(*params).step = 0;
	(*params).links_count = 0;
	(*params).rooms_count = 0;
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

int	room_push_back(t_room_list *rooms, t_params *params, int which_room)
{
	//ft_printf("1TEST%s\n", "TEST");
	int i;
	t_room_list *link;
	t_room_list	*list;

	i = 0;
	list = rooms;
	if (!(link = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	if (!(link->room = (t_room *)malloc(sizeof(t_room))))
		return (0);
	link->room->which_room = which_room;
	link->room->distance = 0;
	link->room->links = NULL;
	link->room->enter = NULL;
	link->room->usage = 0;
	while ((*params).buf[i] && (*params).buf[i] != ' ')
		i++;
	link->room->name = ft_strsub((*params).buf, 0, i++);
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		link->room->x = ft_atoi(&params->buf[i]);
	else
		return (0);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i++] != ' ')
		return (0);
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		link->room->y = ft_atoi(&params->buf[i]);
	else
		return(0);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if (i != (int)ft_strlen((*params).buf))
		return(0);

	link->next = NULL;
	while (list)
		list = list->next;
	list = link;
	list->next = NULL;

	rooms = list;

	while (list)
	{//ft_printf("2TEST%s\n", "TEST");
		ft_printf("name%s x%d y%d dist%d\n", (list)->room->name,
			(list)->room->x, (list)->room->y, (list)->room->which_room);
		list = list->next;
	}
	return (1);
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
		queue->room->usage = 2;
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
				new->room = links->room;
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

int search_way(t_room_list *farm, t_params *params)
{
	int count;

	t_room_list *queue;

	t_room_list *tmp_queue;
	t_room_list *tmp_queue1;
	t_room_list *tmp_rooms;
	t_ways *all_paths;

	all_paths = NULL;
	count = 0;
	queue = NULL;
	tmp_rooms = farm;

	if (!(queue = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	queue->next = NULL;
	while (tmp_rooms && tmp_rooms->room->which_room != START_ROOM)
		tmp_rooms = tmp_rooms->next;
	queue->room = tmp_rooms->room;
	queue->room->distance = (*params).step++;
	queue->room->usage = 1;
	queue->room->enter = queue->room;
	tmp_rooms = farm;
	tmp_queue = queue;

	while (queue)
	{
		if (queue->room->usage != 2)
		{
			if (!add_to_queue(queue, params))
				break ;
		}
		ft_printf("2queue%s x%d y%d whichroom%d usage%d dist%d enter%s\n", (queue)->room->name,
			(queue)->room->x, (queue)->room->y, (queue)->room->which_room,
		(queue)->room->usage, (queue)->room->distance, queue->room->enter->name);
		queue = queue->next;
	}
	queue = tmp_queue;
	/*if (tmp_queue)
		return (0);*/
	while (queue)
	{
		ft_printf("2queue%s x%d y%d whichroom%d usage%d dist%d enter%s\n", (queue)->room->name,
			(queue)->room->x, (queue)->room->y, (queue)->room->which_room,
		(queue)->room->usage, (queue)->room->distance, queue->room->enter->name);
		queue = queue->next;
	}
	queue = tmp_queue;
	//tmp_queue = queue;
	while (tmp_rooms)
	{
		tmp_queue1 = tmp_rooms->room->links;
		ft_printf("1head%s x%d y%d dist%d\n", (tmp_rooms)->room->name,
			(tmp_rooms)->room->x, (tmp_rooms)->room->y, (tmp_rooms)->room->which_room);
		while (tmp_queue1)
		{
		ft_printf("1links%s x%d y%d dist%d\n", tmp_queue1->room->name,
			tmp_queue1->room->x, tmp_queue1->room->y, tmp_queue1->room->which_room);
		tmp_queue1 = tmp_queue1->next;
	}
	tmp_rooms = tmp_rooms->next;
}

	if (!(all_paths = (t_ways *)malloc(sizeof(t_ways *))))
		return (0);
	create_path(all_paths, queue);
	/*tmp_rooms = farm;
	while (tmp_rooms)
	{
		tmp_queue1 = tmp_rooms->room->links;
		ft_printf("1head%s x%d y%d dist%d\n", (tmp_rooms)->room->name,
			(tmp_rooms)->room->x, (tmp_rooms)->room->y, (tmp_rooms)->room->which_room);
		while (tmp_queue1)
		{
		ft_printf("1links%s x%d y%d dist%d\n", tmp_queue1->room->name,
			tmp_queue1->room->x, tmp_queue1->room->y, tmp_queue1->room->which_room);
		tmp_queue1 = tmp_queue1->next;
	}
	tmp_rooms = tmp_rooms->next;
}*/
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

int	make_link(t_room_list *rooms, t_params *params)
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
	list = rooms;
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
		list = rooms;
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

int if_room(t_params *params, t_room **rooms, int which_room)
{
	if ((*params).buf[0] != '#' && ft_strchr((*params).buf, ' '))
	{
		if (ft_strchr((*params).buf, '-'))
		{
			ft_strdel(&params->buf);
			ft_printf("%s\n", "ERROR1");
			return (0);
		}
		if (!save_room(rooms, params, which_room))
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

int comments_parsing(t_params *params, int *ifstart, int *ifend, t_room **rooms)
{
	if (!ft_strstr(&params->buf[2], "start") && !ft_strstr(&params->buf[2], "end"))
	{
		ft_printf("buf3 %s\n", (*params).buf);
		ft_strdel(&params->buf);
		return(1);
	}
	if ((*params).buf[1] == '#' && ft_strstr(&params->buf[2], "start"))
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
			(*params).rooms_count++;
			return(1);
		}
	}
	if ((*params).buf[1] == '#' && ft_strstr(&params->buf[2], "end"))
	{
		if ((*params).ants == 0)
		{
			ft_strdel(&params->buf);
			return (0);
		}
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
			(*params).rooms_count++;
			return(1);
		}
	}
	return(1);
}

int pre_comments_parsing(t_params *params)
{
	if ((*params).buf[1] == '#' && (ft_strstr(&params->buf[2], "start")
	|| ft_strstr(&params->buf[2], "end")))
	{
		ft_printf("buf3 %s\n", (*params).buf);
		ft_strdel(&params->buf);
		return(0);
	}
	else
		return (1);
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

int	save_link(t_link **head, t_params *params)
{

	int i;
	t_link	*newelem;

	i = 0;
	newelem = NULL;
	if ((*params).buf[0] == '#' || !ft_strchr((*params).buf, '-'))
		return (0);
	if (!(newelem = (t_link *)malloc(sizeof(t_link))))
		return (0);

	if ((*params).buf[0] == '#' || !ft_strchr((*params).buf, '-'))
		return (0);
	while ((*params).buf[i] && (*params).buf[i] != '-')
		i++;
	newelem->first = ft_strsub((*params).buf, 0, i);
	i++;
	if (!(*params).buf[i])
		return (0);
	newelem->second = ft_strsub((*params).buf, i, ft_strlen((*params).buf - 1 + 1));
	newelem->next = *head;
	*head = newelem;
	return (1);
}

int	save_room(t_room **head, t_params *params, int which_room)
{
	int i;
	t_room *new_room;

	i = 0;
	//list = rooms;
	if (!(new_room = (t_room *)malloc(sizeof(t_room))))
		return (0);
	new_room->which_room = which_room;
	new_room->distance = 0;
	new_room->links = NULL;
	new_room->enter = NULL;
	new_room->usage = 0;
	while ((*params).buf[i] && (*params).buf[i] != ' ')
		i++;
	new_room->name = ft_strsub((*params).buf, 0, i++);
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		new_room->x = ft_atoi(&params->buf[i]);
	else
		return (0);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i++] != ' ')
		return (0);
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		new_room->y = ft_atoi(&params->buf[i]);
	else
		return(0);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if (i != (int)ft_strlen((*params).buf))
		return(0);

	new_room->next = *head;
	*head = new_room;


	/*while (head)
	{
		ft_printf("name%s x%d y%d dist%d\n", (head)->name,
			(head)->x, (head)->y, (head)->which_room);
		head = head->next;
	}*/
	return (1);
}

int create_links(t_room_list **farm, t_link *links)
{
	t_room_list	*tmplist1;
	t_room_list	*tmplist2;

	tmplist1 = NULL;
	tmplist2 = NULL;

	t_room	*link;
	t_room	*head;
	t_room_list	*list;

	head = NULL;
	link = NULL;
	list = *farm;
	while (list)
	{
		if (ft_strcmp(list->room->name, links->first) == 0)
			head = list->room;
		if (ft_strcmp(list->room->name, links->second) == 0)
			link = list->room;
		list = list->next;
	}
	if (!head || !link)
		return (0);
	if (!(tmplist1 = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	tmplist1->next = head->links;
	head->links = tmplist1;
	tmplist1->room = link;
	if (!(tmplist2 = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	tmplist2->next = link->links;
	link->links = tmplist2;
	tmplist2->room = head;
	return (1);
}

int add_links(t_room_list **farm, t_link *links, t_params *params)
{
	t_room_list	*tmplist1;
	t_room_list	*tmplist2;
	t_room_list	*list;
	tmplist1 = NULL;
	tmplist2 = NULL;
	while (links)
	{
		create_links(farm, links);
		links = links->next;
	}
	ft_printf("%s\n", "non valid");

	list = *farm;
	while (list)
	{
		tmplist1 = list->room->links;
		ft_printf("1head%s x%d y%d dist%d\n", (list)->room->name,
			(list)->room->x, (list)->room->y, (list)->room->which_room);
		while (tmplist1)
		{
		ft_printf("1links%s x%d y%d dist%d\n", tmplist1->room->name,
			tmplist1->room->x, tmplist1->room->y, tmplist1->room->which_room);
		tmplist1 = tmplist1->next;
	}
	list = list->next;
	}
	search_way(*farm, params);
	return (1);
}

int make_rooms_with_links(t_room *rooms, t_link *links, t_params *params)
{
	t_room_list *farm;
	t_room_list *head;
	//t_room_list *tmp_rooms;

	if (!(farm = (t_room_list *)malloc(sizeof(t_room_list))))
		return (0);
	head = farm;
	while (rooms)
	{
		farm->room = rooms;
		if (rooms->next)
		{
			if (!(farm->next = (t_room_list *)malloc(sizeof(t_room_list))))
				return (0);
		}
		else
			farm->next = NULL;
		rooms = rooms->next;
		farm = farm->next;
	}
	ft_printf("%s\n", "non valid");
	farm = head;
	/*while (farm)
	{
		tmp_rooms = farm->room->links;
		ft_printf("1head%s x%d y%d dist%d\n", (farm)->room->name,
			(farm)->room->x, (farm)->room->y, (farm)->room->which_room);
		while (tmp_rooms)
		{
			ft_printf("1links%s x%d y%d dist%d\n", tmp_rooms->room->name,
				tmp_rooms->room->x, tmp_rooms->room->y, tmp_rooms->room->which_room);
			tmp_rooms = tmp_rooms->next;
		}
		farm = farm->next;
	}*/
	if (!add_links(&farm, links, params))
		return (0);
	return (1);
}

int lemin_reading(t_params *params)
{
	int ifstart;
	int ifend;
	t_room *rooms;
	t_link *links;

	ifstart = 0;
	ifend = 0;
	rooms = NULL;
	links = NULL;
	while (get_next_line(0, &params->buf) > 0)
	{
		if (ft_strcmp((*params).buf, "\n") == 0 || (*params).buf[0] == 'L')
		{
			ft_printf("%s\n", "non valid");
			return (0);
		}

		if (!ft_strchr((*params).buf, '-') && (*params).buf[0] != '#'
		&& if_room(params, &rooms, OTHER_ROOM))
		{
			ft_printf("%s\n", "room");
			(*params).rooms_count++;
			if (!(*params).links_count)
				continue ;
			else
			{
				ft_strdel(&params->buf);
				ft_printf("%s\n", "ERROR7");
				break ;
			}
		}
		else if ((*params).buf[0] == '#' &&
		comments_parsing(params, &ifstart, &ifend, &rooms))
		{
			ft_printf("%s\n", "comment");
			continue ;
		}

		else if (ft_strchr((*params).buf, '-') && save_link(&links, params))
		{
			ft_printf("%s\n", "link");
			(*params).links_count++;
			continue ;
		}
		else
		{
			ft_strdel(&params->buf);
			ft_printf("%s\n", "ERROR8");
			return (0);
		}
	}
	make_rooms_with_links(rooms, links, params);
	/*while (links)
	{
		ft_printf("name%s %s\n", (links)->first,
			(links)->second);
		links = links->next;
	}*/
	/*while (rooms)
	{
		ft_printf("name%s x%d y%d dist%d\n", (rooms)->name,
			(rooms)->x, (rooms)->y, (rooms)->which_room);
		rooms = rooms->next;
	}*/
	return (1);
}


int main(void)
{
	t_params params;
	struct_nulling(&params);
	while (get_next_line(0, &params.buf) > 0 && params.buf[0] == '#')
	{
		if (!pre_comments_parsing(&params))
			return (0);
	}
	if (!ants_saving(&params))
		return (0);
	if (!lemin_reading(&params))
	{
		ft_strdel(&params.buf);
		ft_printf("%s\n", "ERROR9");
		return (0);
	}
}
