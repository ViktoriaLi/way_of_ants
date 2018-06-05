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
