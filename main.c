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

int	room_push_back(t_room_list **begin_list, char *content, int which_room)
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
	while (content[i] && content[i] != ' ')
		i++;
	//oneelem->distance = 0;
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
		ft_printf("name%s x%d y%d dist%d\n", (list)->room->name,
			(list)->room->x, (list)->room->y, (list)->room->which_room);
		list = list->next;
	}
	return (1);
}

int	make_link(t_room_list *begin_list, char **content)
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
	if ((*content)[0] == '#' || !ft_strchr(*content, '-'))
		return (0);
	while ((*content)[i] && (*content)[i] != '-')
		i++;
	first = ft_strsub((*content), 0, i);
	i++;
	if (!(*content)[i])
		return (0);
	second = ft_strsub((*content), i, ft_strlen((*content) - 1 + 1));
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

int if_room(char **buf, t_room_list **rooms, int which_room)
{
	//ft_printf("%s \n", "test2");
	//ft_printf("if_room%s \n", *buf);
	if ((*buf)[0] != '#' && ft_strchr(*buf, ' ') && ft_strcmp(*buf, "\n") != 0 && (*buf)[0] != 'L')
	{
		if (ft_strchr(*buf, '-'))
		{
			ft_strdel(buf);
			ft_printf("%s\n", "ERROR1");
			return (0);
		}
		if (!room_push_back(rooms, *buf, which_room))
		{
			ft_strdel(buf);
			ft_printf("%s\n", "ERROR2");
			return (0);
		}
		ft_printf("buf1 %s\n", *buf);
		ft_strdel(buf);
		return (1);
	}
	return (0);
}

int comments_parsing(char **buf, int *ifstart, int *ifend, t_room_list **rooms)
{
	if ((*buf)[0] == '#' && (*buf)[1] != '#' /*&& !ft_strchr(*buf, ' ') && !ft_strchr(*buf, '-')*/)
	{
			ft_printf("buf2 %s\n", *buf);
			ft_strdel(buf);
			return(1);
	}
	if ((*buf)[0] == '#' && (*buf)[1] == '#' && !ft_strstr(&(*buf)[2], "start") && !ft_strstr(&(*buf)[2], "end"))
	{
		ft_printf("buf3 %s\n", *buf);
		ft_strdel(buf);
		return(1);
	}
	if ((*buf)[0] == '#' && (*buf)[1] == '#' && (ft_strstr(&(*buf)[2], "start") || ft_strstr(&(*buf)[2], "end")))
	{
		if (ft_strstr(&(*buf)[2], "start"))
		{
			if (*ifstart != 0)
			{
				ft_printf("%s\n", "ERROR3");
				ft_strdel(buf);
				return (0);
			}
			else
			{
				(*ifstart) = 1;
				ft_printf("buf4 %s\n", *buf);
				ft_strdel(buf);
				get_next_line(0, buf);
				if (!if_room(buf, rooms, 1))
					return(0);
				//ft_printf("buf5 %s\n", *buf);
				return(1);
			}
		}
		if (ft_strstr(&(*buf)[2], "end"))
		{
			if (*ifend != 0)
			{
				ft_printf("%s\n", "ERROR4");
				ft_strdel(buf);
				return (0);
			}
			else
			{
				(*ifend) = 1;
				ft_printf("buf6 %s\n", *buf);
				ft_strdel(buf);
				get_next_line(0, buf);
				if (!if_room(buf, rooms, 2))
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
	int i;
	int ifstart;
	int ifend;

	char *buf;
	//int count;
	int ants;
	//int links_count;
	//int rooms_count;
	buf = NULL;

	//t_list *all_lines;
	t_room_list *rooms;
	t_link *links;
	//t_link *tmp;
	i = 0;
	rooms = NULL;
	//count = 0;
	//all_lines = NULL;
	ants = 0;
	ifstart = 0;
	ifend = 0;
	//links_count = 0;
	//rooms_count = 0;
	links = NULL;
	//tmp = rooms;
	while (get_next_line(0, &buf) > 0 && buf[0] == '#')
	{
		if (!comments_parsing(&buf, &ifstart, &ifend, &rooms))
			return (0);
	}
	if (buf[0] < '1' || buf[0] > '9')
	{
		ft_strdel(&buf);
		ft_printf("%s\n", "ERROR5");
		return (0);
	}
	while (buf[i] > '0' && buf[i] <= '9')
		i++;
	if (buf[i])
	{
		ft_strdel(&buf);
		ft_printf("%s\n", "ERROR6");
		return (0);
	}
		ants = ft_atoi(buf);
		ft_printf("buf8 %s\n", buf);
		ft_printf("ants %d\n", ants);
		ft_strdel(&buf);
		//ft_printf("%s \n", "test");
	while (get_next_line(0, &buf) > 0)
	{
		if (ft_strcmp(buf, "\n") == 0 || buf[0] == 'L')
		{
			ft_strdel(&buf);
			ft_printf("%s\n", "ERROR7");
			return (0);
		}
		//ft_printf("BUF%s\n", buf);
		//else
			//list_push_back(&all_lines, buf);
		//ft_printf("ANTS %d\n", ants);
		//ft_printf("%s \n", "test1");
		if (if_room(&buf, &rooms, 0))
		{
			if (!links)
				continue ;
			else
			{
				ft_strdel(&buf);
				ft_printf("%s\n", "ERROR7");
				return (0);
			}
		}
		//ft_printf("%s \n", "test3");
		if (comments_parsing(&buf, &ifstart, &ifend, &rooms))
			continue ;
		if (make_link(rooms, &buf))
				continue ;
		/*else if (buf[0] != '#')
		{
			ft_strdel(&buf);
			ft_printf("%s\n", "ERROR");
			return (0);
		}*/
		//all_lines = all_lines->next;
		ft_strdel(&buf);
		ft_printf("%s\n", "ERROR8");
		break ;
	}
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
