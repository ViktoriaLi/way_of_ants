int	room_push_back(t_link **begin_list, char *content, int which_room)
{
	int i;
	t_room	*oneelem;
	t_link *link;

	t_link	*list;

	i = 0;
	oneelem = NULL;
	link = NULL;
	list = *begin_list;
	if (!(link = (t_link *)malloc(sizeof(t_link))))
		return (0);
	if (!(oneelem = (t_room *)malloc(sizeof(t_room))))
		return (0);
	//oneelem = ft_lstnew(content, ft_strlen(content));
	link->next = NULL;
	link->link = oneelem;
	while (content[i] && content[i] != ' ')
		i++;
	oneelem->next = NULL;
	oneelem->distance = 0;
	oneelem->which_room = which_room;
	oneelem->links = NULL;
	oneelem->name = ft_strsub(content, 0, i);
	//ft_printf("name%s\n", oneelem->name);
	i++;
	if (content[i] >= '0' && content[i] <= '9')
		oneelem->x = ft_atoi(&content[i]);
	else
		return (0);
	//ft_printf("x%d \n", oneelem->x);
	while (content[i] >= '0' && content[i] <= '9')
		i++;
	if (content[i] != ' ')
		return (0);
	i++;
	if (content[i] >= '0' && content[i] <= '9')
		oneelem->y = ft_atoi(&content[i]);
	else
		return(0);
	while (content[i] >= '0' && content[i] <= '9')
		i++;
	if (i != (int)ft_strlen(content))
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
		ft_printf("name%s x%d y%d dist%d\n", (list)->link->name,
			(list)->link->x, (list)->link->y, (list)->link->which_room);
		list = list->next;
	}
	return (1);
}

int	make_link(t_link **begin_list, char **content)
{
	int i;
	int if_present;
	char *first;
	char *second;
	t_link	*list;
	t_room	*link;
	t_room	*head;

	i = 0;
	if_present = 0;
	head = NULL;
	link = NULL;
	list = *begin_list;
	if ((*content)[0] == '#' || !ft_strchr(*content, '-'))
		return (0);
	while ((*content)[i] && (*content)[i] != '-')
		i++;
	first = ft_strsub((*content), 0, i);
	i++;
	if (!(*content)[i])
		return (0);
	second = ft_strsub((*content), i, ft_strlen((*content) - 1 + 1));
	ft_printf("link%s\n", *content);
	ft_printf("first%s\n", first);
	ft_printf("second%s\n", second);
	while (*begin_list)
	{
		if (ft_strcmp((*begin_list)->link->name, first) == 0)
		{
			head = (*begin_list)->link;
			ft_printf("1first%s\n", head->name);
			if_present++;
		}
		(*begin_list) = (*begin_list)->next;
	}
	if (if_present != 1)
		return(0);
	if_present = 0;
	(*begin_list) = list;
	while ((*begin_list))
	{
		if (ft_strcmp((*begin_list)->link->name, second) == 0)
		{
			link = (*begin_list)->link;
			ft_printf("2first%s\n", link->name);
			if_present++;
		}
		(*begin_list) = (*begin_list)->next;
	}
	if (if_present != 1)
		return(0);
	//head = link;

	if (!(head->links))
	{
		head->links = link;
		*begin_list = list;
		return (1);
	}
	while (head->links)
		head->links = head->next;
	head->links = link;
	*begin_list = list;
	while (list)
	{
		ft_printf("1head%s x%d y%d dist%d\n", (list)->link->name,
			(list)->link->x, (list)->link->y, (list)->link->which_room);
		while (list->link->links)
		{
			ft_printf("1links%s x%d y%d dist%d\n", (list)->link->links->name,
				(list)->link->links->x, (list)->link->links->y, (list)->link->links->which_room);
			list->link->links = list->link->links->next;
		}
		list = list->next;
	}
	//head = *begin_list;
		/*while (head->link->next)
		{
			head->link = head->link->next;
			ft_printf("1name%s x%d y%d dist%d\n", head->link->name,
			head->link->x, head->link->y, head->link->distance);
		}*/

	return (1);
	/*
	if (!(oneelem = (t_link *)malloc(sizeof(t_link))))
		return (0);
	oneelem->link = link->link;
	oneelem->next = NULL;
	*begin_list = oneelem;f*/
}

//working
void add_to_queue(t_room_list *queue)
{
	t_room_list *tmp;
	t_room_list *tmp1;
	t_room_list *tmp_queue;

	tmp = NULL;
	tmp_queue = queue;
	tmp1 = queue;
	ft_printf("1add%s x%d y%d dist%d %s\n", (tmp_queue)->room->name,
		(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room, queue->room->enter->name);
	if (tmp_queue->room->links)
		tmp_queue->room->usage = 2;
	while (tmp_queue->room->links)
	{
		if (!(tmp = (t_room_list *)malloc(sizeof(t_room_list))))
			return ;
			tmp->next = NULL;
			tmp = tmp_queue->room->links;
			tmp->room->usage = 1;
			tmp->room->distance = 1;
			tmp->room->enter = tmp1->room;
			tmp_queue->next = tmp;
			ft_printf("2add%s x%d y%d dist%d %s\n", (tmp_queue)->room->name,
				(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room, tmp_queue->room->enter->name);
			//tmp_queue = tmp_queue->next;
		tmp_queue->room->links = tmp_queue->room->links->next;
	}
}

void add_to_queue(t_room_list *queue)
{
	t_room_list *tmp;
	t_room_list *tmp1;
	t_room_list *tmp_queue;
	t_room_list *tmp_queue1;

	tmp = NULL;
	tmp_queue = queue;
	tmp_queue1 = queue;
	tmp1 = queue;
	while (tmp_queue)
		tmp_queue = tmp_queue->next;
	//ft_printf("1add%s x%d y%d dist%d %s\n", (tmp_queue)->room->name,
		//(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room, queue->room->enter->name);
	if (tmp_queue1->room->links)
		tmp_queue1->room->usage = 2;
	ft_printf("1room%s\n", "test");
	while (tmp_queue1->room->links)
	{
		ft_printf("start%s x%d y%d dist%d %s\n", (tmp_queue1)->room->name,
			(tmp_queue1)->room->x, (tmp_queue1)->room->y, (tmp_queue1)->room->which_room, tmp_queue1->room->enter->name);
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
			tmp_queue = tmp;
			ft_printf("9room%s\n", "test");
			ft_printf("2add%s x%d y%d dist%d %s\n", (tmp_queue)->room->name,
				(tmp_queue)->room->x, (tmp_queue)->room->y, (tmp_queue)->room->which_room, tmp_queue->room->enter->name);
			tmp_queue->next = NULL;
			tmp_queue = tmp_queue->next;
			ft_printf("10room%s\n", "test");
		tmp_queue1->room->links = tmp_queue1->room->links->next;
	}
}

void add_to_queue(t_room_list *queue)
{
	ft_printf("startstart%s x%d y%d dist%d %s\n", (queue)->room->name,
		(queue)->room->x, (queue)->room->y, (queue)->room->which_room, queue->room->enter->name);
	t_room_list *tmp;
	t_room_list *tmp1;
	t_room_list *tmp_queue;
	t_room_list *tmp_queue1;

	tmp = NULL;
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
		tmp_queue1->room->links = tmp_queue1->room->links->next;
	}
}

/*while (list)
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
