#include "lem_in.h"

void struct_nulling(t_params *params)
{
	(*params).buf = NULL;
	(*params).ants = 0;
	(*params).step = 0;
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
	//oneelem = ft_lstnew(content, ft_strlen(content));
	while ((*params).buf[i] && (*params).buf[i] != ' ')
		i++;
	//oneelem->distance = 0;
	oneelem->which_room = which_room;
	oneelem->distance = 0;
	oneelem->links = NULL;
	oneelem->enter = NULL;
	oneelem->usage = 0;
	oneelem->name = ft_strsub((*params).buf, 0, i);
	//if (which_room == START_ROOM)

	//ft_printf("name%s\n", oneelem->name);
	i++;
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		oneelem->x = ft_atoi(&params->buf[i]);
	else
		return (0);
	//ft_printf("x%d \n", oneelem->x);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i] != ' ')
		return (0);
	i++;
	if ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		oneelem->y = ft_atoi(&params->buf[i]);
	else
		return(0);
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if (i != (int)ft_strlen((*params).buf))
		return(0);
	//ft_printf("y%d \n", oneelem->y);
	//link->link = oneelem;
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

/*void add_to_queue(t_room_list *queue)
{
	ft_printf("startstart%s x%d y%d dist%d %s\n", (queue)->room->name,
		(queue)->room->x, (queue)->room->y, (queue)->room->which_room, queue->room->enter->name);
	t_room_list *tmp;
	t_room_list *tmp1;
	t_room_list *tmp2;
	t_room_list *tmp_queue;
	t_room_list *tmp_queue1;

	tmp = NULL;
	tmp2 = NULL;
	tmp_queue = queue;
	tmp_queue1 = queue;
	tmp1 = queue;
	//ft_printf("1add%s x%d y%d dist%d %s\n", (tmp_queue)->room->name,
		//(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room, queue->room->enter->name);
	if (tmp_queue1->room->links)
		tmp_queue1->room->usage = 2;
	ft_printf("1room%s\n", "test");
	while (tmp_queue1->room->links)
	{
		tmp2 = tmp_queue1->room->links;
		ft_printf("2room%s\n", "test");
		if (!(tmp = (t_room_list *)malloc(sizeof(t_room_list))))
			return ;
			ft_printf("3room%s\n", "test");
			tmp->next = NULL;
			ft_printf("4room%s\n", "test");
			tmp = tmp_queue1->room->links;
			ft_printf("5room%s\n", "test");
			tmp->room->usage = 1;
			ft_printf("6room%s\n", "test");
			tmp->room->distance = 1;
			ft_printf("7room%s\n", "test");
			tmp->room->enter = tmp1->room;
			ft_printf("8room%s\n", "test");
			while (tmp_queue->next)
				tmp_queue = tmp_queue->next;
			tmp_queue->next = tmp;
			ft_printf("9room%s\n", "test");
			ft_printf("2add%s x%d y%d dist%d %s\n", (tmp_queue1)->room->links->room->name,
				(tmp_queue1)->room->links->room->x, (tmp_queue1)->room->links->room->y,
				(tmp_queue1)->room->links->room->which_room, tmp_queue1->room->links->room->enter->name);
			tmp_queue = tmp_queue->next;
			tmp_queue->next = NULL;
			ft_printf("10room%s\n", "test");
			//tmp_queue = queue;
			//tmp_queue1 = tmp;
		tmp_queue1->room->links = tmp_queue1->room->links->next;
	}
}*/

void add_to_queue(t_room_list *queue)
{
	ft_printf("startstart%s x%d y%d dist%d %s\n", (queue)->room->name,
		(queue)->room->x, (queue)->room->y, (queue)->room->which_room, queue->room->enter->name);
	t_room_list *tmp;
	t_room_list *tmp1;
	t_room_list *tmp2;
	t_room_list *tmp_queue;
	t_room_list *tmp_queue1;

	tmp = NULL;
	tmp2 = NULL;
	tmp_queue = queue;
	tmp_queue1 = queue;
	tmp1 = queue;
	//ft_printf("1add%s x%d y%d dist%d %s\n", (tmp_queue)->room->name,
		//(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room, queue->room->enter->name);
	if (tmp_queue1->room->links)
		tmp_queue1->room->usage = 2;
	ft_printf("1room%s\n", "test");
	while (tmp_queue1->room->links)
	{
		tmp2 = tmp_queue1->room->links;
		ft_printf("2room%s\n", "test");
		if (!(tmp = (t_room_list *)malloc(sizeof(t_room_list))))
			return ;
			ft_printf("3room%s\n", "test");
			tmp->next = NULL;
			ft_printf("4room%s\n", "test");
			tmp = tmp_queue1->room->links;
			ft_printf("5room%s\n", "test");
			tmp->room->usage = 1;
			ft_printf("6room%s\n", "test");
			tmp->room->distance = 1;
			ft_printf("7room%s\n", "test");
			tmp->room->enter = tmp1->room;
			ft_printf("8room%s\n", "test");
			while (tmp_queue->next)
				tmp_queue = tmp_queue->next;
			tmp_queue->next = tmp;
			ft_printf("9room%s\n", "test");
			ft_printf("2add%s x%d y%d dist%d %s\n", (tmp_queue1)->room->links->room->name,
				(tmp_queue1)->room->links->room->x, (tmp_queue1)->room->links->room->y,
				(tmp_queue1)->room->links->room->which_room, tmp_queue1->room->links->room->enter->name);
			tmp_queue = tmp_queue->next;
			tmp_queue->next = NULL;
			ft_printf("10room%s\n", "test");
			//tmp_queue = queue;
			//tmp_queue1 = tmp;
		tmp_queue1->room->links = tmp_queue1->room->links->next;
	}
}

void search_way(t_room_list *rooms)
{
	t_room_list *tmp;
	t_room_list *tmp1;
	t_room_list *queue;
	t_room_list *tmp_queue;
	t_room_list *tmp_rooms;

	queue = NULL;
	tmp = NULL;
	tmp1 = NULL;
	tmp_rooms = rooms;
	if (!(queue = (t_room_list *)malloc(sizeof(t_room_list))))
		return ;
	while (tmp_rooms->room->which_room != START_ROOM)
		tmp_rooms = tmp_rooms->next;
	tmp1 = tmp_rooms;
	tmp_queue = queue;
	tmp_queue->room = tmp_rooms->room;
	tmp_queue->next = NULL;
	tmp_queue->room->distance = 0;
	tmp_queue->room->usage = 1;
	if (tmp_rooms->room->links)
		tmp_queue->room->usage = 2;
	while (tmp_rooms->room->links)
	{
		if (!(tmp = (t_room_list *)malloc(sizeof(t_room_list))))
			return ;
			tmp->next = NULL;
			tmp = tmp_rooms->room->links;
			tmp->room->usage = 1;
			tmp->room->distance = 1;
			tmp->room->enter = tmp1->room;
			tmp_queue->next = tmp;
			tmp_queue = tmp_queue->next;
		tmp_rooms->room->links = tmp_rooms->room->links->next;
	}
	ft_printf("15room%s\n", "test");
	tmp_queue = queue;
	{
		ft_printf("1queue%s x%d y%d whichroom%d usage%d dist%d\n", (tmp_queue)->room->name,
			(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room,
		(tmp_queue)->room->usage, (tmp_queue)->room->distance);
		tmp_queue = tmp_queue->next;
	}
	tmp_queue = queue;
	while (tmp_queue->room->usage != 1)
		tmp_queue = tmp_queue->next;
	while (tmp_queue)
	{
		add_to_queue(tmp_queue);
		tmp_queue = tmp_queue->next;
	}
	tmp_queue = queue;
	while (tmp_queue)
	{
		ft_printf("2queue%s x%d y%d whichroom%d usage%d dist%d\n", (tmp_queue)->room->name,
			(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room,
		(tmp_queue)->room->usage, (tmp_queue)->room->distance);
		tmp_queue = tmp_queue->next;
	}
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
	int if_present;

	i = 0;
	head = NULL;
	link = NULL;
	tmplist = NULL;
	if_present = 0;
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

int	save_link(t_link **begin_list, char **content)
{
	int i;
	t_link	*list;
	t_link	*oneelem;

	i = 0;
	oneelem = NULL;
	list = *begin_list;
	if (!(oneelem = (t_link *)malloc(sizeof(t_link))))
		return (0);
	//oneelem = ft_lstnew(content, ft_strlen(content));
	oneelem->next = NULL;
	if ((*content)[0] == '#' || !ft_strchr(*content, '-'))
		return (0);
	while ((*content)[i] && (*content)[i] != '-')
		i++;
	oneelem->first = ft_strsub((*content), 0, i);
	i++;
	if (!(*content)[i])
		return (0);
	oneelem->second = ft_strsub((*content), i, ft_strlen((*content) - 1 + 1));
	/*ft_printf("link%s\n", *content);
	ft_printf("first%s\n", first);
	ft_printf("second%s\n", second);*/
	if (!(*begin_list))
	{
		*begin_list = oneelem;
		return (1);
	}
	while ((*begin_list)->next)
		(*begin_list) = (*begin_list)->next;
	(*begin_list)->next = oneelem;
	*begin_list = list;
	/*while (list)
	{
		ft_printf("links_saved%s %s\n", (list)->first, (list)->second);
		list = list->next;
	}*/
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


int main(void)
{
	t_params params;

	int i;
	int ifstart;
	int ifend;
	t_room_list *rooms;
	t_link *links;
	//int count;
	int links_count;
	//int rooms_count;
	//t_list *all_lines;
	//t_link *tmp;
	//count = 0;
	//all_lines = NULL;
	i = 0;
	rooms = NULL;
	ifstart = 0;
	ifend = 0;
	links = NULL;
	links_count = 0;
	//rooms_count = 0;
	//tmp = rooms;
	struct_nulling(&params);
	while (get_next_line(0, &params.buf) > 0 && params.buf[0] == '#')
	{
		if (!comments_parsing(&params, &ifstart, &ifend, &rooms))
			return (0);
	}
	if (params.buf[0] < '1' || params.buf[0] > '9')
	{
		ft_strdel(&params.buf);
		ft_printf("%s\n", "ERROR5");
		return (0);
	}
	while (params.buf[i] > '0' && params.buf[i] <= '9')
		i++;
	if (params.buf[i])
	{
		ft_strdel(&params.buf);
		ft_printf("%s\n", "ERROR6");
		return (0);
	}
		params.ants = ft_atoi(params.buf);
		ft_printf("buf8 %s\n", params.buf);
		ft_printf("ants %d\n", params.ants);
		ft_strdel(&params.buf);
		//ft_printf("%s \n", "test");
	while (get_next_line(0, &params.buf) > 0)
	{
		if (ft_strcmp(params.buf, "\n") == 0 || params.buf[0] == 'L')
		{
			ft_strdel(&params.buf);
			ft_printf("%s\n", "ERROR7");
			return (0);
		}
		//ft_printf("BUF%s\n", buf);
		//else
			//list_push_back(&all_lines, buf);
		//ft_printf("ANTS %d\n", ants);
		//ft_printf("%s \n", "test1");
		if (if_room(&params, &rooms, OTHER_ROOM))
		{
			if (!links_count)
				continue ;
			else
			{
				ft_strdel(&params.buf);
				ft_printf("%s\n", "ERROR7");
				break ;
			}
		}
		//ft_printf("%s \n", "test3");
		if (comments_parsing(&params, &ifstart, &ifend, &rooms))
			continue ;
		if (make_link(rooms, &params))
		{
			links_count++;
			continue ;
		}

		/*else if (buf[0] != '#')
		{
			ft_strdel(&buf);
			ft_printf("%s\n", "ERROR");
			return (0);
		}*/
		//all_lines = all_lines->next;
		ft_strdel(&params.buf);
		ft_printf("%s\n", "ERROR8");
		break ;
	}
	search_way(rooms);
	//make_link(links, rooms);
	while (rooms)
	{
		ft_printf("name%s x%d y%d dist%d\n", (rooms)->room->name,
			(rooms)->room->x, (rooms)->room->y, (rooms)->room->which_room);
		rooms = rooms->next;
	}
	while (links)
	{
		ft_printf("links_saved%s %s\n", (links)->first, (links)->second);
		links = links->next;
	}
	//ft_printf("%s\n", "test");
	/*while (rooms)
	{
		while (tmp->link->next)
		{
			tmp->link = tmp->link->next;
			ft_printf("1name%s x%d y%d dist%d\n", tmp->link->name,
			tmp->link->x, tmp->link->y, tmp->link->distance);
		}
		ft_printf("2name%s x%d y%d dist%d\n", rooms->link->name,
			rooms->link->x, rooms->link->y, rooms->link->distance);
		rooms = rooms->next;
	}*/
}
