#include "lem_in.h"

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

int	room_push_back(t_link **begin_list, char *content)
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
	oneelem->links = NULL;
	oneelem->name = ft_strsub(content, 0, i);
	ft_printf("name%s\n", oneelem->name);
	i++;
	if (content[i] >= '0' && content[i] <= '9')
		oneelem->x = ft_atoi(&content[i]);
	else
		return (0);
	ft_printf("x%d \n", oneelem->x);
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
	ft_printf("y%d \n", oneelem->y);
	//link->link = oneelem;
	if (!list)
	{
		*begin_list = link;
		return (1);
	}
	while (list->next)
	{
		ft_printf("name%s x%d y%d dist%d\n", (list)->link->name, 
			(list)->link->x, (list)->link->y, (list)->link->distance);
		
		list = list->next;
	}
	list->next = link;
	/*while (*begin_list)
	{
		ft_printf("111%s\n", "test");
		ft_printf("name%s x%d y%d dist%d\n", (*begin_list)->link->name, 
			(*begin_list)->link->x, (*begin_list)->link->y, (*begin_list)->link->distance);
		*begin_list = (*begin_list)->next;
	}*/
	return (1);
}

int	make_link(t_link **begin_list, char *content)
{
	int i;
	int if_present;
	char *first;
	char *second;
	t_link	*list;
	t_link	*link;
	t_link	*head;
	//t_link *oneelem;
	//t_room *new_link;

	i = 0;
	if_present = 0;
	//oneelem = NULL;
	head = NULL;
	link = NULL;
	list = *begin_list;
	while (content[i] && content[i] != '-')
		i++;
	first = ft_strsub(content, 0, i);
	i++;
	if (!content[i])
		return (0);
	second = ft_strsub(content, i, ft_strlen(content - 1 + 1));
	ft_printf("link%s\n", content);
	ft_printf("first%s\n", first);
	ft_printf("second%s\n", second);
	while (list)
	{
		if (ft_strcmp(list->link->name, first) == 0)
		{
			head = list;
			if_present++;
		}
		list = list->next;
	}
	if (if_present != 1)
		return(0);
	if_present = 0;
	list = *begin_list;
	while (list)
	{
		if (ft_strcmp(list->link->name, second) == 0)
		{
			link = list;
			if_present++;
		}
		list = list->next;
	}
	if (if_present != 1)
		return(0);
	head->link = link->link;
	if (!head->link)
	{
		head->link = link->link;
		*begin_list = head;
		return (1);
	}
	while (head->link->next)
		head->link = head->link->next;
	head->link = link->link;
	*begin_list = head;
	head = *begin_list;
		while (head->link->next)
		{
			head->link = head->link->next;
			ft_printf("1name%s x%d y%d dist%d\n", head->link->name, 
			head->link->x, head->link->y, head->link->distance);
		}

	return (1);
	/*
	if (!(oneelem = (t_link *)malloc(sizeof(t_link))))
		return (0);
	oneelem->link = link->link;
	oneelem->next = NULL;
	*begin_list = oneelem;f*/
}

int main(void)
{
	char *buf;
	int count;
	int ants;
	buf = NULL;
	t_list *all_lines;
	t_link *rooms;
	//t_link *tmp;

	rooms = NULL;
	count = 0;
	all_lines = NULL;
	ants = 0;
	//tmp = rooms;
	while (get_next_line(0, &buf) > 0)
	{
		if (ft_strcmp(buf, "\n") == 0 || buf[0] == 'L')
		{
			ft_strdel(&buf);
			ft_printf("%s\n", "ERROR");
			return (0);
		}
		ft_printf("BUF%s\n", buf);
		if (count == 0)
		{
			ants = ft_atoi(buf);
			count++;
			ft_strdel(&buf);
			continue;
		}
		else
			list_push_back(&all_lines, buf);
		ft_printf("ANTS %d\n", ants);
		if (buf[0] != '#' && count != 0 && ft_strchr(buf, ' '))
		{
			if (ft_strchr(buf, '-'))
			{
				ft_strdel(&buf);
				ft_printf("%s\n", "ERROR");
				return (0);
			}
			if (!room_push_back(&rooms, buf))
			{
				ft_strdel(&buf);
				ft_printf("%s\n", "ERROR");
				return (0);
			}
			ft_strdel(&buf);
		}
		else if (buf[0] != '#' && count != 0 && ft_strchr(buf, '-'))
		{
			make_link(&rooms, buf);
		}
		else if (buf[0] != '#' && count != 0)
		{
			ft_strdel(&buf);
			ft_printf("%s\n", "ERROR");
			return (0);
		}
		//all_lines = all_lines->next;
		ft_strdel(&buf);
		count++;
	}
	ft_printf("%s\n", "test");
	while (rooms)
	{
		/*while (tmp->link->next)
		{
			tmp->link = tmp->link->next;
			ft_printf("1name%s x%d y%d dist%d\n", tmp->link->name, 
			tmp->link->x, tmp->link->y, tmp->link->distance);
		}*/
		
		ft_printf("2name%s x%d y%d dist%d\n", rooms->link->name, 
			rooms->link->x, rooms->link->y, rooms->link->distance);
		rooms = rooms->next;
	}
}